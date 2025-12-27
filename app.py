from flask import Flask, render_template, request

app = Flask(__name__)

# -------------------- Disease Linked List --------------------
class Disease:
    def __init__(self, name, symptoms):
        self.name = name
        self.symptoms = symptoms
        self.symptom_count = len(symptoms)
        self.next = None

# Insert disease at the end
def insert_disease(head, name, symptoms):
    new_node = Disease(name, symptoms)
    if head is None:
        return new_node
    temp = head
    while temp.next:
        temp = temp.next
    temp.next = new_node
    return head

# Calculate weighted score
def calculate(user_symptoms, disease_symptoms):
    score = 0
    for u in user_symptoms:
        for d in disease_symptoms:
            if u == d:
                if d in ["fever", "cough", "chills"]:
                    score += 2
                else:
                    score += 1
    return score

# Probability calculation
def probability(wscore, total_symptoms):
    if total_symptoms == 0:
        return 0
    max_possible = total_symptoms * 2.0
    return (wscore / max_possible) * 100.0

# -------------------- Initialize Diseases --------------------
head = None
head = insert_disease(head, "Flu", ["fever", "headache", "cough"])
head = insert_disease(head, "COVID-19", ["fever", "cough", "fatigue", "loss of smell"])
head = insert_disease(head, "Malaria", ["fever", "chills", "sweating"])
head = insert_disease(head, "Dengue", ["fever", "headache", "joint pain", "rash"])
head = insert_disease(head, "Typhoid", ["fever", "headache", "abdominal pain", "diarrhea"])
head = insert_disease(head, "Pneumonia", ["fever", "cough", "chest pain", "fatigue"])
head = insert_disease(head, "Migraine", ["headache", "nausea", "sensitivity to light", "dizziness"])
head = insert_disease(head, "Tuberculosis", ["cough", "fever", "night sweats", "weight loss"])
head = insert_disease(head, "Asthma", ["cough", "shortness of breath", "chest tightness", "wheezing"])
head = insert_disease(head, "Allergy", ["sneezing", "rash", "itchy eyes", "fatigue"])
head = insert_disease(head, "Food Poisoning", ["nausea", "vomiting", "diarrhea", "abdominal pain"])
head = insert_disease(head, "Hepatitis", ["fatigue", "nausea", "jaundice", "abdominal pain"])
head = insert_disease(head, "Strep Throat", ["sore throat", "fever", "headache", "swollen lymph nodes"])

all_symptoms = [
    "fever", "headache", "cough", "fatigue", "loss of smell",
    "chills", "sweating", "joint pain", "rash", "abdominal pain",
    "diarrhea", "chest pain", "nausea", "sensitivity to light",
    "dizziness", "night sweats", "weight loss", "shortness of breath",
    "chest tightness", "wheezing", "sneezing", "itchy eyes",
    "vomiting", "jaundice", "sore throat", "swollen lymph nodes"
]

# -------------------- Routes --------------------
@app.route("/", methods=["GET", "POST"])
def index():
    results = None
    best_disease = None
    best_prob = -1

    if request.method == "POST":
        selected_indices = request.form.getlist("symptoms")
        selected_symptoms = [all_symptoms[int(i)] for i in selected_indices]

        temp = head
        results = []

        while temp:
            score = calculate(selected_symptoms, temp.symptoms)
            prob = probability(score, temp.symptom_count)
            results.append({"name": temp.name, "prob": round(prob, 2)})
            if prob > best_prob:
                best_prob = prob
                best_disease = temp.name
            temp = temp.next

    return render_template(
        "index.html",
        symptoms=all_symptoms,
        results=results,
        best_disease=best_disease,
        best_prob=round(best_prob, 2)
    )

if __name__ == "__main__":
    app.run(debug=True)
