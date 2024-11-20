import csv
from faker import Faker
import random
import base64

fake = Faker()

def generate_citizen():
    """Generate a single citizen record."""
    name = fake.first_name()
    surname = fake.last_name()
    
    # Generate date of birth
    birth_day = random.randint(1, 28)
    birth_month = random.randint(1, 12)
    birth_year = random.randint(1950, 2010)
    date_of_birth = f"{birth_day:02d}{birth_month:02d}{birth_year % 100:02d}"

    # First 2 digits: ASCII of the first character of name
    first_part = f"{ord(name[0]):02d}"

    # Second 2 digits: ASCII of the first character of surname
    second_part = f"{ord(surname[0]):02d}"

    # Third 6 digits: Date of birth in ddmmyy
    third_part = date_of_birth

    # Fourth 2 digits: Base64 encoding-derived value
    random_number = random.randint(1, 1000)
    combined_string = f"{name}{surname}{date_of_birth}{random_number}"
    base64_encoded = base64.b64encode(combined_string.encode()).decode()
    fourth_part = f"{sum(ord(c) for c in base64_encoded[-2:]):02d}"[-2:]  # Take the last 2 digits

    # Fifth digit: Check digit
    raw_digits = f"{first_part}{second_part}{third_part}{fourth_part}"
    check_digit = sum(int(d) for d in raw_digits) % 10  # Example formula for check digit
    fifth_part = str(check_digit)

    citizenID = f"{first_part}{second_part}{third_part}{fourth_part}{fifth_part}"

    gender = random.choice(["MALE", "FEMALE"])
    status = random.choice(["SINGLE"])
    personState = random.choice(["ALIVE", "DECEASED", "DISAPPEARED", "UNKNOWN"])
    religion = random.choice(["Christianity", "Islam", "Hinduism", "Buddhism", "Judaism", "Other"])
    fatherRecordID = ''.join([str(random.randint(0, 9)) for _ in range(13)])
    motherRecordID = ''.join([str(random.randint(0, 9)) for _ in range(13)])
    spouseID = '-'

    address = {
        "houseNo": str(random.randint(1, 9999)),
        "street": fake.street_name(),
        "city": fake.city(),
        "province": fake.state(),
        "postcode": fake.postcode()
    }
    return (
        name, surname, citizenID, gender, status, personState, religion,
        fatherRecordID, motherRecordID, {
            "date": birth_day, "month": birth_month, "year": birth_year
        }, address, spouseID
    )

def save_citizens_to_csv(filename, count):
    """Generate citizens and save them to a CSV file."""
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow([
            "name", "surname", "citizenID", "gender", "status", "personState",
            "religion", "fatherRecordID", "motherRecordID", "date", "month", "year",
            "houseNo", "street", "city", "province", "postcode", "spouseID"
        ])
        for _ in range(count):
            (name, surname, citizenID, gender, status, personState, religion,
             fatherRecordID, motherRecordID, date, address, spouseID) = generate_citizen()
            writer.writerow([
                name, surname, citizenID, gender, status, personState, religion,
                fatherRecordID, motherRecordID, date["date"], date["month"], date["year"],
                address["houseNo"], address["street"], address["city"], address["province"], address["postcode"],
                spouseID
            ])

# Generate 100 citizens and save to a CSV
save_citizens_to_csv("citizens.csv", 10000)
