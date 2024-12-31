import csv

# Load actual solutions into a dictionary
actual_solutions = {}
with open('internet_bests.csv', 'r') as actual_file:
    reader = csv.reader(actual_file)
    next(reader)
    for row in reader:
        problem, value = row
        actual_solutions[problem] = float(value)

# Process the report file
with open('all_reports.csv', 'r') as report_file:
    reader = csv.reader(report_file)
    next(reader)
    for row in reader:
        problem = row[0]
        report_value = float(row[4])  # Assuming the value is in the 5th column
        actual_value = actual_solutions.get(problem)

        if actual_value is not None:
            if actual_value >= report_value:
                print(f"{problem}: Wow! {row[2]}+{row[3]} got better than internet best. Expected {actual_value}, got {report_value}.")
        else:
            print(f"Problem {problem}: No actual value found.")
