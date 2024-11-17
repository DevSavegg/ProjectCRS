import csv
from faker import Faker
import random

fake = Faker()

def generate_citizen():
    """Generate a single citizen record."""
    name = fake.first_name()
    surname = fake.last_name()
    citizenID = ''.join([str(random.randint(0, 9)) for _ in range(13)])
    date = {"date": random.randint(1, 28), "month": fake.month_name(), "year": random.randint(1950, 2010)}
    address = {
        "houseNo": str(random.randint(1, 9999)),
        "street": fake.street_name(),
        "city": fake.city(),
        "province": fake.state(),
        "postcode": fake.postcode()
    }
    contact = {"phone": fake.phone_number()[:10], "email": fake.email()}
    return (name, surname, citizenID, date, address, contact)

def save_citizens_to_csv(filename, count):
    """Generate citizens and save them to a CSV file."""
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["name", "surname", "citizenID", "date", "month", "year", "houseNo", "street", "city", "province", "postcode", "phone", "email"])
        for _ in range(count):
            name, surname, citizenID, date, address, contact = generate_citizen()
            writer.writerow([
                name, surname, citizenID,
                date["date"], date["month"], date["year"],
                address["houseNo"], address["street"], address["city"], address["province"], address["postcode"],
                contact["phone"], contact["email"]
            ])


# Generate citizens and save to a CSV
save_citizens_to_csv("citizens.csv", 2500)