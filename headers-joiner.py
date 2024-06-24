import os

# List of header files to combine
# RESPECT THE ORDER of #includes

HEADER_FILES = [
    "./include/Common.h",
    "./include/Strings.h",
    "./include/Vectors.h",
    "./include/Queue.h",
    "./include/MPSC.h",
    "./include/Stack.h",
    "./include/Testlib.h",
    "./include/Logger.h",
]

# Set to store unique #include statements
INCLUDES = set()


def read_file_lines(path):
    """Read lines from a file."""
    with open(path, 'r') as f:
        return f.readlines()


def filter_macros(lines):
    """Filter out #include and ifndef/define statements."""
    filtered_lines = []
    skip_next_line = False  # Flag to skip the next line after finding #ifndef or #define
    for line in lines:
        if skip_next_line:
            skip_next_line = False
            continue
        if line.startswith('#ifndef'):
            skip_next_line = True  # Skip the next line after #ifndef or #define
            continue
        elif line.startswith("#endif"):
            continue
        elif line.startswith('#include "'):
            # Skip local includes within headers already combined
            continue
        elif line.startswith('#include <'):
            # Collect system includes to add to the combined header
            INCLUDES.add(line)
        else:
            filtered_lines.append(line)
    return filtered_lines


# List to store contents of each header file after filtering
FILES_CONTENTS = []

# Process each header file
for header_file in HEADER_FILES:
    contents = filter_macros(read_file_lines(header_file))
    FILES_CONTENTS.append(contents)

# Write to the combined header file
try:
    os.mkdir("./build")
except:
    pass

combined_header = "./build/cthings.h"
with open(combined_header, "w") as f:
    f.write("#ifndef C_THINGS\n")
    f.write("#define C_THINGS\n\n")
    f.writelines(sorted(INCLUDES))

    for file_contents in FILES_CONTENTS:
        f.writelines(file_contents)

    f.write("#endif // C_THINGS\n")

print(f"[INFO]: Combined headers into {combined_header}")
