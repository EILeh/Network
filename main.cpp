/* Network
 *
 * Description
 *
 * Program stores information of who has recruited who. Program asks the user to
 * give a command S, P, C, D or Q. Commands can be given also as a lowercase
 * letters.
 * S (=store): Takes two persons' identifiers as a string parameters. First
 * parameter is a person who has recruited the person as a second parameter.
 * P (=print): Takes the person's identifier as string parameter and prints all
 * the others that the particular person has recruited and who they have
 * recruited. They are printed in the order where they are recruited and if
 * person 1 has recruited person 2 and 3 and person 3 has recruited person 4,
 * would it look like this:
 * P 1
 * ..2
 * ..3
 * ....4
 * C (=count): Takes the person's identifier as a parameter and prints the size
 * of the current person's subnet.
 * D (=depth=: Takes the person's identifier as a parameter and prints the depth
 * of the current person's subnet meaning the longest recruited line that the
 * person has starting from the person themself. If person 1 has recruited
 * person 2 and person 2 has recruited person 3, the depth on the person 1's
 * subnet would be 3.
 * Q (=quit): Program closes.
 *
 * Writer of the program
 *
 * Name: EILeh
 *
 */


#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using Network = std::unordered_map<std::string, std::vector<std::string>>;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        // Finds from every fileline a separator and stores its' location to a
        // variable new_part.
        std::string new_part = tmp.substr(0, tmp.find(delimiter));

        // Variable tmp starts splitting after the separator.
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());

        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }

    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }

    return result;
}

// Stores the information from the marketers.
void store(std::string const &id1, std::string const &id2, Network &NetWork)
{


    // Checks if the person (id1) who recruits the other person (id2) is found
    // from the database. If it is found, a new person (id2) is added to it.
    if ( NetWork.find(id1) == NetWork.end() )
    {
        NetWork.insert( {id1, {}} );
    }

    // Checks if the recruited person (id2) is found from the database. If per-
    // son (id2) is found, a new data structure is added in case they want to
    // recuite someone.
    if ( NetWork.find(id2) == NetWork.end() )
    {
        NetWork.insert( {id2, {}} );
    }

    // If neither of them is found, a new key-value -pair is added to the data-
    // base.
    NetWork.at(id1).push_back(id2);
}

// Prints the subnet of the wanted person.
void print_recursive(std::string const &id, Network const &NetWork,
                     std::string const dots = "")
{
    // Prints the dots and the person's name.
    std::cout << dots << id << std::endl;

    // Initializes a vector to go through the subnet.
    std::vector<std::string> SubNetWork = NetWork.at(id);

    // Goes through the subnet and the function calls itself. With the recursive
    // function the '..' is being printed before the name if the recruiter al-
    // ready has subnet.
    for ( std::string const &marketer : SubNetWork )
    {
        print_recursive(marketer, NetWork, dots + "..");
    }
}

// Counts how many persons the recruiter has recruited and how many persons
// they have recruited.
int count_recursive(std::string const &id, Network const &NetWork)
{
    // Initializes the variable that stores the information of the recruited
    // persons.
    int result = 0;

    // Goes through the unordered_map on a particular person and the function
    // calls itself. Adds to the variable result the current value of the func-
    // tion count_recursive + 1. Returns the result.
    for ( std::string const &marketer : NetWork.at(id) )
    {
        result += 1 + count_recursive(marketer, NetWork);
    }

    return result;
}

// Counts how many persons the particular peson has been able to recruite.
int depth_recursive(std::string const &id, Network const &NetWork)
{
    // Initializes the variable deth_record that stores the information of the
    // deepest subnet.
    int depth_record = 0;

    // Goes through the unordered_map on a particular person and the function
    // calls itself. Adds to the variable depth the current value of the func-
    // tion depth_recursive.
    for ( std::string const &marketer : NetWork.at(id) )
    {
        int depth = depth_recursive(marketer, NetWork);

        // Checks if the depth is more than the current depth_record. If so,
        // the new depth_record is the depth.
        // Tarkistetaan onko syvyys suurempi kuin tämän hetkinen suurin syvyys
        // depth_record. Jos näin on, tallennetaan depth_record uusi suurin sy-
        // vyys depth.
        if ( depth > depth_record )
        {
            depth_record = depth;

        }

    }

    // Returns the depth_record + 1.
    return depth_record + 1;
}

int main()
{
    Network NetWork;


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            store(id1, id2, NetWork);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print_recursive(id, NetWork);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << count_recursive(id, NetWork) << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << depth_recursive(id, NetWork) << std::endl;



        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
