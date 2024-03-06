import argparse
import re

def getNumClasses(labelmap_path):
    with open(labelmap_path, 'r') as l:
        labelmap = l.read()

    return labelmap.count('id:')


def adjust_config(config_file, train_input_path, eval_input_path, checkpoint_path, checkpoint_type, num_classes, batch_size, label_map, bfloat16):
    with open(config_file, 'r') as f:
        config = f.read()

    # Adjust input_path variables in train_input_reader
    config = re.sub(r"(train_input_reader\s{(?:\s.*:\s*.*)*\s*tf_record_input_reader\s*{\s*input_path:\s*)\"(.*)\"", r'\g<1>"' + train_input_path + '"', config)

    # Adjust input_path variables in eval_input_reader
    config = re.sub(r"(eval_input_reader\s{(?:\s.*:\s*.*)*\s*tf_record_input_reader\s*{\s*input_path:\s*)\"(.*)\"", r'\g<1>"' + eval_input_path + '"', config)

    # Adjust num_classes
    config = re.sub("fine_tune_checkpoint:\s*(?:\"(.*?)\")?(\d+(?:.\d+)?)?(?:(\w+))?", f'fine_tune_checkpoint: "{checkpoint_path}"', config)

    # Adjust num_classes
    config = re.sub("fine_tune_checkpoint_type:\s*(?:\"(.*?)\")?(\d+(?:.\d+)?)?(?:(\w+))?", f'fine_tune_checkpoint_type: "{checkpoint_type}"', config)

    # Adjust num_classes
    config = re.sub("num_classes:\s*(?:\"(.*?)\")?(\d+(?:.\d+)?)?(?:(\w+))?", f'num_classes: {num_classes}', config)

    # Adjust batch_size
    config = re.sub("batch_size:\s*(?:\"(.*?)\")?(\d+(?:.\d+)?)?(?:(\w+))?", f'batch_size: {batch_size}', config)

    # Adjust batch_size
    config = re.sub("(label_map:|label_map_path:\s*)(?:\"(.*?)\")?(\d+(?:.\d+)?)?(?:(\w+))?", r'\g<1>"' + label_map + '"', config)

    # Adjust batch_size
    rightFormatBfloat = 'true' if bfloat16 else 'false'
    config = re.sub("use_bfloat16:\s*(?:\"(.*?)\")?(\d+(?:.\d+)?)?(?:(\w+))?", f'bfloat16: {rightFormatBfloat}', config)

    with open(config_file, 'w') as f:
        f.write(config)

def main():
    parser = argparse.ArgumentParser(description='Adjust configuration file.')
    parser.add_argument('--config_file', type=str, help='Path to the .config file')
    parser.add_argument('--train_input_path', type=str, help='Path to the training data TFRecord file')
    parser.add_argument('--eval_input_path', type=str, help='Path to the evaluation data TFRecord file')
    parser.add_argument('--checkpoint_path', type=str, help='Path of the checkpoint')
    parser.add_argument('--checkpoint_type', type=str, help='Type of the checkpoint detection|classification', default="detection")
    parser.add_argument('--batch_size', type=int, help='Batch size', default=1)
    parser.add_argument('--label_map', type=str, help='Path to the label_map')
    parser.add_argument('--bfloat16', type=bool, help='use bfloat16? true|false', default=False)

    args = parser.parse_args()

    num_classes = getNumClasses(args.label_map)

    adjust_config(args.config_file, args.train_input_path, args.eval_input_path, args.checkpoint_path, args.checkpoint_type, num_classes, args.batch_size, args.label_map, args.bfloat16)

if __name__ == "__main__":
    main()

# \s.*:\s*\"(.*)\"
# .*:\s*(?:\"(.*?)\")?(\d+(?:.\d+)?)?(?:(\w+))?
