#include <iostream>
#include <map>
using namespace std;
enum PaymentStatus {
    AUTHORIZE, CAPTURE, CANCEL, QUERY
};

struct payment {
    string user_id;
    long long amount;
    PaymentStatus status;
};


int main() {
    int n;
    cin >> n;

    map<string, payment> paymentsDB;
    map<string,  long long> userMoneyDB;

    for (int i=0 ; i<n ;i++) {
        string cmd ;
        cin >> cmd;

        if (cmd =="AUTHORIZE") {
            long long  amount;
            string tx_id, user_id;
            cin >> tx_id >> user_id>> amount;
            if (paymentsDB.find(tx_id) == paymentsDB.end()) {
                paymentsDB[tx_id].status = AUTHORIZE;
                paymentsDB[tx_id].user_id= user_id;
                paymentsDB[tx_id].amount = amount;
            }

        } else if (cmd=="CAPTURE") {
            string tx_id;
            cin >> tx_id;
            if (paymentsDB.find(tx_id) != paymentsDB.end() && paymentsDB[tx_id].status == AUTHORIZE) {
                paymentsDB[tx_id].status = CAPTURE;
                userMoneyDB[paymentsDB[tx_id].user_id] += paymentsDB[tx_id].amount;
            }

        } else if (cmd =="CANCEL") {
            string tx_id;
            cin >> tx_id;
            if (paymentsDB.find(tx_id) != paymentsDB.end() && paymentsDB[tx_id].status == AUTHORIZE) {
                paymentsDB[tx_id].status = CANCEL;
            }

        } else if (cmd=="QUERY") {
            string user_id;
            cin >> user_id;
            if (userMoneyDB.find(user_id) != userMoneyDB.end()) {
                cout << userMoneyDB[user_id]<< endl;
            }else {
                cout << "0" << endl;
            }

        } else {
            cout << "not found instruction";
        }
    }
}
