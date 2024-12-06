#!/bin/bash

# Define variables
DATASET="car.data"
RUNS=20
SUMMARY_FILE="summary.txt"
ALL_METRICS_FILE="all_metrics.csv"

# Clean previous files
rm -f $SUMMARY_FILE $ALL_METRICS_FILE

# Write header to the consolidated metrics file
echo "Total Number of Runs,Train Split Ratio,Run#,Accuracy (Best IG),Accuracy (Top 3 IG),Accuracy (Best Gini),Accuracy (Top 3 Gini),Training Time (Best IG),Training Time (Top 3 IG),Training Time (Best Gini),Training Time (Top 3 Gini)" >> $ALL_METRICS_FILE

for SPLIT in $(seq 40 10 90)
do
    echo "Running with train_split_ratio=$SPLIT..."
    
    # Run the program, redirecting stdout to the summary file
    ./main $DATASET $RUNS $SPLIT >> $SUMMARY_FILE

    echo "" >> $SUMMARY_FILE

    # Append metrics.csv to the consolidated file with additional columns
    while IFS= read -r line || [ -n "$line" ]; do
        # Skip the header line from metrics.csv
        if [[ $line == "Run,"* ]]; then
            continue
        fi
        # Append metrics with additional columns for runs and split ratio
        echo "$RUNS,$SPLIT,$line" >> $ALL_METRICS_FILE
    done < metrics.csv

    echo "Completed for train_split_ratio=$SPLIT"
done

echo "All experiments completed. Summary stored in $SUMMARY_FILE, metrics in $ALL_METRICS_FILE."
