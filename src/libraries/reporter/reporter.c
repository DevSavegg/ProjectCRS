#include "reporter.h"
#include "../utils/utils.h"
#include "../finder/finder.h"
// Private Functions

// Public Functions

void printCitizenInfo(char id[255]) {
    Citizen cit[10];
    char gender[21], fstatus[21], state[21], month[21];
    int status = fetchByCitizenID(cit, id);
    
    if(status <= 0) printf("not found.\n");
    for(int i = 0; i < status; i++){
    genderToString(cit[i].gender, gender);
    statusToString(cit[i].status, fstatus);
    personStateToString(cit[i].personState, state);
    strMonth(cit[i].dateOfBirth.month, month);
//name, surname, ID, status, personState, religion, fatherRecordID, motherRecordID, date_buffer, address_id, gender
    printf("+--------------------------------------------------------+\n");
    printf("|                   Citizen Profile                      |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|    Citizen's ID:      %-13s                    |\n", cit[i].citizenID);
    printf("|    Name:   %-10s Surname:   %-10s            |\n", cit[i].name, cit[i].surname);
    printf("|    Gender:      %-19s                    |\n", gender);
    printf("|                                                        |\n");
    printf("|    Date of Birth:    %2d/%-11s/%4d               |\n", cit[i].dateOfBirth.date, month, cit[i].dateOfBirth.year);
    printf("|                                                        |\n");
    printf("|    Religion:    %-22s                 |\n", cit[i].religion);
    printf("|                                                        |\n");
    printf("|    Status:    %-24s                 |\n", fstatus);
    printf("|    State:    %-25s                 |\n", state);
    printf("+--------------------------------------------------------+\n");
    printf("|                       Address                          |\n");
    printf("+--------------------------------------------------------+\n");
    printf("|   House No.   %-5s           St. %-20s |\n", cit[i].address.houseNo, cit[i].address.street);
    printf("|   City        %-15s                          |\n", cit[i].address.city);
    printf("|   Province    %-15s Post Code   %-5s        |\n", cit[i].address.province, cit[i].address.postcode);
    printf("+--------------------------------------------------------+\n");
    }
}
