import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

# Reload the dataset
data = pd.read_csv('all_metrics.csv')

# Extract unique Train Split Ratios
train_split_ratios = data['Train Split Ratio'].unique()

# Plot function for Best, Average, and Worst metrics
def plot_best_avg_worst(data, metric, y_label, title, ylim, pdf):
    plt.figure(figsize=(10, 6))
    bar_width = 0.2
    indices = list(range(len(train_split_ratios)))
    best_values, avg_values, worst_values = [], [], []
    
    for ratio in sorted(train_split_ratios):
        subset = data[data['Train Split Ratio'] == ratio]
        if 'Accuracy' in metric:
            # For accuracy, best is max, worst is min
            best_values.append(subset[metric].max())
            worst_values.append(subset[metric].min())
        else:
            # For training time, best is min, worst is max
            best_values.append(subset[metric].min())
            worst_values.append(subset[metric].max())
        
        avg_values.append(subset[metric].mean())
    
    # Plot bars for Best, Average, Worst
    plt.bar([i - bar_width for i in indices], best_values, width=bar_width, color=(33/255, 150/255, 243/255), label='Best')
    plt.bar(indices, avg_values, width=bar_width, color=(251/255, 128/255, 114/255), label='Average')
    plt.bar([i + bar_width for i in indices], worst_values, width=bar_width, color=(90/255, 90/255, 90/255), label='Worst')
    
    # Set x-ticks and labels
    plt.xticks(indices, [f'{ratio}%' for ratio in sorted(train_split_ratios)])
    
    # Customize plot
    plt.title(title)
    plt.xlabel('Train Split Ratio (%)')
    plt.ylabel(y_label)
    if ylim:
        plt.ylim(ylim)
    plt.legend(title='Metric Type', loc='upper left')
    plt.grid(False)
    plt.tight_layout()
    
    # Save to PDF
    pdf.savefig()
    plt.close()

# Plot function for Standard Deviation and Coefficient of Variation (only for Accuracy)
def plot_std_cv(data, metric, y_label, title, pdf):
    plt.figure(figsize=(10, 6))
    bar_width = 0.3
    indices = list(range(len(train_split_ratios)))
    std_values, cv_values = [], []
    
    for ratio in sorted(train_split_ratios):
        subset = data[data['Train Split Ratio'] == ratio]
        
        if 'Accuracy' in metric:
            # Calculate Standard Deviation and Coefficient of Variation for Accuracy
            std_values.append(subset[metric].std())
            cv_values.append((std_values[-1] / subset[metric].mean()) * 100 if subset[metric].mean() != 0 else 0)
        else:
            std_values.append(0)  # For training time, set Std Dev to 0
            cv_values.append(0)   # For training time, set CV to 0
    
    # Plot Std Dev and CV as separate bars
    plt.bar([i - bar_width + 0.1 for i in indices], std_values, width=bar_width, color=(0/255, 128/255, 0/255), label='Std Dev')
    plt.bar([i + bar_width - 0.1 for i in indices], cv_values, width=bar_width, color=(255/255, 165/255, 0/255), label='CV (%)')
    
    # Set x-ticks and labels
    plt.xticks(indices, [f'{ratio}%' for ratio in sorted(train_split_ratios)])
    
    # Customize plot
    plt.title(title)
    plt.xlabel('Train Split Ratio (%)')
    plt.ylabel(y_label)
    plt.legend(title='Metric Type', loc='best')
    plt.grid(False)
    plt.tight_layout()
    
    # Save to PDF
    pdf.savefig()
    plt.close()

# Plot function for Line Charts (Accuracies or Times across Runs)
def plot_line_chart(data, metric, y_label, title, ylim, pdf):
    plt.figure(figsize=(10, 6))
    for ratio in sorted(train_split_ratios):
        subset = data[data['Train Split Ratio'] == ratio]
        plt.plot(subset['Run#'], subset[metric], marker='o', label=f'Train Split {ratio}%')
    
    # Customize plot
    plt.title(title)
    plt.xlabel('Run#')
    plt.ylabel(y_label)
    if ylim:
        plt.ylim(ylim)
    plt.legend(title='Train Split Ratio', loc='upper left')
    plt.grid(True)
    plt.tight_layout()
    
    # Save to PDF
    pdf.savefig()
    plt.close()

# Define the metrics and their y-axis limits
metrics_info = [
    ("Accuracy (Best IG)", "Accuracy (%)", "Accuracy (Best IG)", (85, 100)),
    ("Accuracy (Top 3 IG)", "Accuracy (%)", "Accuracy (Top 3 IG)", (70, 100)),
    ("Accuracy (Best Gini)", "Accuracy (%)", "Accuracy (Best Gini)", (85, 100)),
    ("Accuracy (Top 3 Gini)", "Accuracy (%)", "Accuracy (Top 3 Gini)", (70, 100)),
    ("Training Time (Best IG)", "Training Time (microseconds)", "Training Time (Best IG)", (1000, 8000)),
    ("Training Time (Top 3 IG)", "Training Time (microseconds)", "Training Time (Top 3 IG)", (2000, 10000)),
    ("Training Time (Best Gini)", "Training Time (microseconds)", "Training Time (Best Gini)", (1000, 9000)),
    ("Training Time (Top 3 Gini)", "Training Time (microseconds)", "Training Time (Top 3 Gini)", (1500, 12000))
]

# Create a PDF to save the plots
with PdfPages('report.pdf') as pdf:
    # Plot line charts for metrics across runs (First Page)
    for metric, y_label, title, ylim in metrics_info:
        plot_line_chart(data, metric, y_label, title, ylim, pdf)
    
    # Plot bar charts for best, average, worst values (Second Page)
    for metric, y_label, title, ylim in metrics_info:
        aggregate_title = f"Best, Average, and Worst {title}"
        plot_best_avg_worst(data, metric, y_label, aggregate_title, ylim, pdf)
    
    # Plot Standard Deviation and Coefficient of Variation (Third Page)
    for metric, y_label, title, ylim in metrics_info:
        if 'Accuracy' in title:  # Only plot Std and CV for Accuracy metrics
            aggregate_title = f"Std Dev and CV for {title}"
            plot_std_cv(data, metric, y_label, aggregate_title, pdf)

print("Plots saved to report.pdf.")
