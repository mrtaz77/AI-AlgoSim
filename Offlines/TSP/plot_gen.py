import sys
import os
import pandas as pd
import matplotlib.pyplot as plt

REQUIRED_COLUMNS = [
    "Graph File", "Graph Name", "Version", "Heuristic", 
    "Best Cost", "Avg Cost", "Worst Cost", 
    "Best Time (µs)", "Avg Time (µs)", "Worst Time (µs)"
]

def file_exists(filename):
    """Check if the file exists."""
    return os.path.isfile(filename)

def is_csv_file(filename):
    """Check if the file has a .csv extension."""
    return filename.lower().endswith('.csv')

def has_required_columns(filename):
    """Check if the file contains all required columns."""
    try:
        df = pd.read_csv(filename)
    except Exception as e:
        return False, f"Error: Could not read the file '{filename}'. {e}"

    missing_columns = [col for col in REQUIRED_COLUMNS if col not in df.columns]
    if missing_columns:
        return False, f"Error: Missing required columns: {', '.join(missing_columns)}"
    
    return True, ""

def validate_csv_file(filename):
    """Run all validation checks and return an appropriate message."""
    if not file_exists(filename):
        return f"Error: The file '{filename}' does not exist."

    if not is_csv_file(filename):
        return f"Error: The file '{filename}' is not a .csv file."

    columns_valid, message = has_required_columns(filename)
    if not columns_valid:
        return message

    return "Valid File"

def plot_metrics(df, graph_file):
    """Plot the six metrics (Cost and Time) for each graph file using grouped histograms with color-coded versions."""
    metrics = ['Best Cost', 'Avg Cost', 'Worst Cost', 'Best Time (µs)', 'Avg Time (µs)', 'Worst Time (µs)']
    metric_labels = ['Best Cost', 'Avg Cost', 'Worst Cost', 'Best Time (µs)', 'Avg Time (µs)', 'Worst Time (µs)']
    
    # Define colors for each version using hex color codes
    version_colors = {'Greedy': '#8DD3C7', 'Semi-Greedy 3': '#FB8072', 'Semi-Greedy 5': '#80B1D3'}
    
    # Create the "plots" directory if it doesn't exist
    os.makedirs("plots", exist_ok=True)
    
    for i, metric in enumerate(metrics):
        plt.figure(figsize=(12, 8))
        plt.title(f"{graph_file} - {metric_labels[i]}")
        plt.xlabel("Heuristic")
        plt.ylabel(metric)
        
        # Filter the data for the current graph file
        graph_data = df[df["Graph File"] == graph_file].copy()
        
        # Group by Heuristic and Version
        heuristics = graph_data["Heuristic"].unique()
        versions = graph_data["Version"].unique()
        version_indices = {version: idx for idx, version in enumerate(versions)}
        
        # Width of each bar and offsets for side-by-side positioning
        num_versions = len(versions)
        bar_width = 0.8 / num_versions
        x_positions = range(len(heuristics))
        
        # Plot bars for each version
        for version in versions:
            version_data = graph_data[graph_data["Version"] == version]
            version_values = [
                version_data[version_data["Heuristic"] == heuristic][metric].mean() if heuristic in version_data["Heuristic"].values else 0
                for heuristic in heuristics
            ]
            bar_positions = [x + bar_width * version_indices[version] for x in x_positions]
            
            plt.bar(
                bar_positions,
                version_values,
                bar_width,
                label=version,
                color=version_colors[version],  # Use hex color codes here
                edgecolor='black'
            )
        
        # Set x-axis ticks and labels
        plt.xticks([x + bar_width * (num_versions / 2 - 0.5) for x in x_positions], heuristics, rotation=90, ha='right')
        
        # Add legend for versions
        plt.legend(title="Version")
        
        # Automatically scale the y-axis and adjust layout
        plt.tight_layout()

        # Save the plot as a PNG file in the "plots" folder
        plot_filename = os.path.join("plots", f"{graph_file}_{metric_labels[i]}.png")
        plt.savefig(plot_filename)
        plt.close()  # Close the plot to avoid displaying it on the screen

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <filename>")
        sys.exit(1)

    filename = sys.argv[1]
    validation_message = validate_csv_file(filename)
    print(validation_message)

    if validation_message != "Valid File":
        sys.exit(1)
    
    df = pd.read_csv(filename)

    for graph_file in df['Graph File'].unique():
        graph_data = df[df['Graph File'] == graph_file]
        plot_metrics(graph_data, graph_file)

if __name__ == "__main__":
    main()
