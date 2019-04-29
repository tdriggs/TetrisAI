import os, json, subprocess
from pathlib import WindowsPath

def get_data_filenames(num_outputs):
    output_depth = {
        41: 1,
        81: 2,
        121: 3,
        161: 4,
        201: 5,
        241: 6
    }[num_outputs]

    return (WindowsPath("../training_data/uber_x_1__%s__%d.csv" % ("training", output_depth)),
            WindowsPath("../training_data/uber_x_1__%s__%d.csv" % ("test", output_depth)))

def main():
    for root, dirs, files in os.walk("../networks/"):
        if (root != "../networks/"):
            continue
        
        for file in files:
            if file.startswith("uber") and file.endswith(".nn"):
                format_data = file.split("__")
                num_outputs = int(format_data[-2])

                training_filename, test_filename = get_data_filenames(num_outputs)
                json_data = {
                    "learning_rate": 0.01,
                    "input_size": 221,
                    "output_size": 201,
                    "hidden_sizes": [1],
                    
                    "training_data": str(training_filename),
                    "test_data": str(test_filename),
                    "training_iterations": 0,
                    
                    "input_network": str(WindowsPath(root, file)),
                    "output_network": str(WindowsPath(root, "validated", file))[:-3]
                }

                with open("./temp_configuration.json", "w") as fp:
                    json.dump(json_data, fp)

                subprocess.run(['..\\bin\\Train\\aiTrainer.exe', '.\\temp_configuration.json'])

                
if __name__ == "__main__":
    main()
