#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

class VotingSystem {
private:
    int NumberOfCandidates;
    int NumberOfStudents;
    string CandidateNames[10];
    int VotesForCandidates[10];
    string AdminPassword;
    string votedIdsFile = "voted_ids.txt";

    bool verifyAdminPassword() {
        string inputPassword;
        cout << "Enter the password: ";
        cin >> inputPassword;
        return inputPassword == AdminPassword;
    }

    bool checkIfVoted(int studentId) {
        ifstream file(votedIdsFile);
        int id;
        while (file >> id) {
            if (id == studentId) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    void markAsVoted(int studentId) {
        ofstream file(votedIdsFile, ios::app);
        file << studentId << endl;
        file.close();
    }

    void vote(int studentId) {
        if (checkIfVoted(studentId)) {
            cout << "You have already voted!" << endl;
            return;
        }
        
        cout << "Student - " << studentId << endl;
        for (int j = 0; j < NumberOfCandidates; ++j) {
            cout << "Press " << (j + 1) << " for " << CandidateNames[j] << endl;
        }
        cout << "Now, Please Put Your Vote: ";
        char ch = getch();
        int vote = ch - '1';
        if (vote >= 0 && vote < NumberOfCandidates) {
            VotesForCandidates[vote]++;
            cout << "(Hidden)" << endl;
            markAsVoted(studentId);
        } else {
            cout << "Invalid vote!" << endl;
        }
    }

public:
    void initialize() {
        cout << "Number of Candidate: ";
        cin >> NumberOfCandidates;
        if (NumberOfCandidates <= 1) {
            cout << "Sorry! Number of Candidate must be more than one person." << endl;
            return;
        }

        for (int i = 0; i < NumberOfCandidates; ++i) {
            cout << "Candidate-" << (i + 1) << " Name: ";
            cin >> CandidateNames[i];
            VotesForCandidates[i] = 0;
        }

        cout << "Number of Students: ";
        cin >> NumberOfStudents;
        cout << "Enter the password for admin: ";
        cin >> AdminPassword;
    }

    void conductElection() {
        if (!verifyAdminPassword()) {
            cout << "Wrong Password! Access denied." << endl;
            return;
        }

        for (int i = 1; i <= NumberOfStudents; ++i) {
            cout << "Online Voting System " << endl;
            cout << "Enter Student ID: ";
            int studentId;
            cin >> studentId;
            vote(studentId);
        }
    }

    void displayResults() {

        cout << "Enter Password to show result: " << endl;
        if (!verifyAdminPassword()) {
            cout << "Wrong Password! Access denied." << endl;
            return;
        }
        cout << "Election Results:" << endl;
        int maxVotes = 0;
        int winnerIndex = -1;
        for (int j = 0; j < NumberOfCandidates; ++j) {
            cout << CandidateNames[j] << " got " << VotesForCandidates[j] << " vote(s)." << endl;
            if (VotesForCandidates[j] > maxVotes) {
                maxVotes = VotesForCandidates[j];
                winnerIndex = j;
            }
        }
        if (winnerIndex != -1) {
            cout << "Congratulations " << CandidateNames[winnerIndex] << ". You are Elected!" << endl;
        } else {
            cout << "No candidate won the election." << endl;
        }
    }
};

int main() {
     VotingSystem election;
    election.initialize();
    cout<<"----------------------------------"<<endl;
    election.conductElection();
    cout<<"----------------------------------"<<endl;
    election.displayResults();
    cout<<"----------------------------------"<<endl;
    return 0;
}
