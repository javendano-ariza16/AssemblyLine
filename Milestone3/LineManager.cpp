// Name: Juan David Avendano
// Seneca Student ID: 165095217
// Seneca email: javendano-ariza@myseneca.ca
// Date of completion: 08 April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<vector>
#include"LineManager.h"
#include"Utilities.h"
#include <algorithm>
namespace sdds {
    
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        std::ifstream infile(file);
        // Checking whether the file was opened successfully
        if (!infile) {
            throw "ERROR: Unable to open file";
        }
        // Reading from the file
        Utilities utils{};
        std::string str{};
        size_t next_pos{ 0 };
        size_t next_copy = next_pos;
        bool more{ true };

        // Designing vectors to determine the first station later in the code
        std::vector<std::string> leftStations;
        std::vector<std::string> rightStations;

        // ===== DESIGN TO FIGURE OUT THE FIRST ELEMENT =====
        while (std::getline(infile, str)) {
            // Resetting the index
            next_pos = next_copy;
            // Storing the names of the current and the next stations
            std::string tempCurrStation{}, tempNextStation{};
            tempCurrStation = utils.extractToken(str, next_pos, more);
            // This is to prevent the program from extracting twice if there is no delimiter and checking if there is a next station that exists
            if (!(next_pos == next_copy)) {
                tempNextStation = utils.extractToken(str, next_pos, more);


                leftStations.push_back(tempCurrStation);
                rightStations.push_back(tempNextStation);
            }
            
            auto currStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                return station->getItemName() == tempCurrStation;
                });
            // Adding the station to the active line
            m_activeLine.push_back(*currStation);

            // Finding the next station in the collection
            if (tempNextStation.length() > 0) {
                auto nextStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return station->getItemName() == tempNextStation;
                    });
                // Setting the next station
                (*currStation)->setNextStation(*nextStation);
            }
        }

        // Algorithm to determine the first station
        size_t count{};
        std::string fStn{};
        for (const auto& leftStation : leftStations) {
            count = 0;
            for (const auto& rightStation : rightStations) {
                if (leftStation == rightStation) {
                    count++;
                }
            }
            if (count == 0) {
                fStn = leftStation;
                break;
            }
        }

        // Setting the fist station
        auto firstStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
            return station->getItemName() == fStn;
            });
        m_firstStation = *firstStation;

        // Setting the count of customer orders that are still pending
        m_cntCustomerOrder = g_pending.size();
    }
    void LineManager::reorderStations() {
        std::vector<Workstation*>tempOrdered;
        Workstation* currentOrder = m_firstStation;
        while (!(currentOrder==nullptr))
        {
            tempOrdered.push_back(currentOrder);
            currentOrder = currentOrder->getNextStation();
        }
       m_activeLine = tempOrdered;
    };
    bool LineManager::run(std::ostream& os) 
    {
        static size_t counIterations=0;
        counIterations++;
        os << "Line Manager Iteration: " << counIterations << std::endl;
        if(!g_pending.empty())
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [&](auto& i) {
                i->fill(os);
            });


        std::for_each(m_activeLine.begin(), m_activeLine.end(),
            [&](auto& i) {
                i->attemptToMoveOrder();
            });

        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    };
    void LineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto station) {
            station->display(os);
            });
    }
}
