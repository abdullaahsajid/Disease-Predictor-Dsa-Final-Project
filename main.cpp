#include <iostream>
#include <string>
using namespace std;


struct disease {
    string name;
    string symptoms[10];
    int symptomCount;
    disease *next;
};

void insertdisease(disease* &head, string name, string arr[], int count) {
    disease* newNode = new disease;
    newNode->name = name;
    newNode->symptomCount = count;
    for(int i=0; i<count; i++)
        newNode->symptoms[i] = arr[i];
    newNode->next = nullptr;

    if(head == nullptr) head = newNode;
    else {
        disease* temp = head;
        while(temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
    }
}

int calculate(string userArr[], int userCount,
                           string diseaseArr[], int diseaseCount) {

    int score = 0;

    for (int i = 0; i < userCount; i++) {
        for (int j = 0; j < diseaseCount; j++) {

            if (userArr[i] == diseaseArr[j]) {

                // --- Major Symptoms ---
                if (diseaseArr[j] == "fever" ||
                    diseaseArr[j] == "cough" ||
                    diseaseArr[j] == "chills")
                {
                    score += 2;
                }
                else {
                    score += 1;
                }
            }
        }
    }
    return score;
}

double probality(int wscore, int totsymptoms) {
    if (totsymptoms == 0) return 0;
    double maxPossible = totsymptoms * 2.0; // each symptom max 2 points
    return (wscore / maxPossible) * 100.0;
}



int main() {

    disease* head = nullptr;

    string fluSymptoms[] = {"fever", "headache", "cough"};
    insertdisease(head, "Flu", fluSymptoms, 3);

    string covidSymptoms[] = {"fever", "cough", "fatigue", "loss of smell"};
    insertdisease(head, "COVID-19", covidSymptoms, 4);

    string malariaSymptoms[] = {"fever", "chills", "sweating"};
    insertdisease(head, "Malaria", malariaSymptoms, 3);

    string dengueSymptoms[] = {"fever", "headache", "joint pain", "rash"};
    insertdisease(head, "Dengue", dengueSymptoms, 4);

    string typhoidSymptoms[] = {"fever", "headache", "abdominal pain", "diarrhea"};
    insertdisease(head, "Typhoid", typhoidSymptoms, 4);

    string pneumoniaSymptoms[] = {"fever", "cough", "chest pain", "fatigue"};
    insertdisease(head, "Pneumonia", pneumoniaSymptoms, 4);

    string migraineSymptoms[] = {"headache", "nausea", "sensitivity to light", "dizziness"};
    insertdisease(head, "Migraine", migraineSymptoms, 4);

    string tbSymptoms[] = {"cough", "fever", "night sweats", "weight loss"};
    insertdisease(head, "Tuberculosis", tbSymptoms, 4);

    string asthmaSymptoms[] = {"cough", "shortness of breath", "chest tightness", "wheezing"};
    insertdisease(head, "Asthma", asthmaSymptoms, 4);

    string allergySymptoms[] = {"sneezing", "rash", "itchy eyes", "fatigue"};
    insertdisease(head, "Allergy", allergySymptoms, 4);

    string foodPoisoningSymptoms[] = {"nausea", "vomiting", "diarrhea", "abdominal pain"};
    insertdisease(head, "Food Poisoning", foodPoisoningSymptoms, 4);

    string hepatitisSymptoms[] = {"fatigue", "nausea", "jaundice", "abdominal pain"};
    insertdisease(head, "Hepatitis", hepatitisSymptoms, 4);

    string strepSymptoms[] = {"sore throat", "fever", "headache", "swollen lymph nodes"};
    insertdisease(head, "Strep Throat", strepSymptoms, 4);

    // ---------- List of ALL Possible Symptoms ----------
    string allSymptoms[] = {
        "fever", "headache", "cough", "fatigue", "loss of smell",
        "chills", "sweating", "joint pain", "rash", "abdominal pain",
        "diarrhea", "chest pain", "nausea", "sensitivity to light",
        "dizziness", "night sweats", "weight loss", "shortness of breath",
        "chest tightness", "wheezing", "sneezing", "itchy eyes",
        "vomiting", "jaundice", "sore throat", "swollen lymph nodes"
    };
    int totsymptoms = 26;

    int choice;
    while(true) {

        cout << "\n===== MENU =====\n";
        cout << "1) Predict disease\n";
        cout << "2) Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {

            cout << "\nAvailable Symptoms:\n";
            for(int i=0; i<totsymptoms; i++)
                cout << i+1 << ") " << allSymptoms[i] << endl;

            cout << "\nEnter symptom numbers (0 to finish):\n";

            string selected[50];
            int count = 0;

            while(true) {
                int num;
                cin >> num;

                if(num == 0)
                    break;
                else if(num >= 1 && num <= totsymptoms) {
                    selected[count++] = allSymptoms[num-1];
                } else {
                    cout << "Invalid symptom number, try again: ";
                }
            }

            if(count == 0) {
                cout << "No symptoms selected, try again.\n";
                continue;
            }

            cout << "\n===== Probability Results =====\n";

            disease* temp = head;
            string bestdisease = "";
            double bestprob = -1;

            while(temp != nullptr) {

                int wscore = calculate(selected, count,
                                                          temp->symptoms, temp->symptomCount);

                double probability = probality(wscore, temp->symptomCount);

                cout << temp->name << ": " << probability << "%\n";

                if(probability > bestprob) {
                    bestprob = probability;
                    bestdisease = temp->name;
                }

                temp = temp->next;
            }

            cout << "\n Most Probable disease: " << bestdisease 
                 << " (" << bestprob << "% match)\n";
        }

        else if(choice == 2) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
