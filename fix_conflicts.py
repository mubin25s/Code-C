import os

import re

def fix_conflicts(directory):
    # Regex to capture the content in HEAD and ignore the rest
    # Pattern: <<<<<<< HEAD\n(content)\n=======\n(content)\n>>>>>>> (hash)
    # We will just keep the HEAD content.
    pattern = re.compile(rb'<<<<<<< HEAD\r?\n(.*?)\r?\n=======\r?\n(.*?)\r?\n>>>>>>> [a-f0-9]+', re.DOTALL)

    for root, dirs, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            try:
                with open(file_path, 'rb') as f:
                    content = f.read()
                
                if b'<<<<<<< HEAD' in content:
                    print(f"Fixing {file_path}...")
                    
                    def replacement(match):
                        head_content = match.group(1)
                        incoming_content = match.group(2)
                        
                        if head_content.strip() == incoming_content.strip():
                            return head_content
                        else:
                            # If they differ, we still keep HEAD as default strategy for 'double codes' 
                            # but print a note.
                            print(f"  Note: Content differed in {file}, keeping HEAD.")
                            return head_content

                    new_content = pattern.sub(replacement, content)
                    
                    if new_content != content:
                        with open(file_path, 'wb') as f:
                            f.write(new_content)
                        print(f"  Fixed.")
            except Exception as e:
                print(f"Error processing {file_path}: {e}")

if __name__ == "__main__":
    fix_conflicts(r"d:\C")
