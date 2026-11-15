import subprocess, tempfile, sys
from pathlib import Path
exe = str(Path(sys.argv[1]).resolve())
def run(folder, inputs):
    return subprocess.run([exe], input=inputs, text=True, cwd=folder, capture_output=True, timeout=5)
with tempfile.TemporaryDirectory() as folder:
    p = Path(folder)
    first = run(folder, '1\n2023-02-29\n2024-02-29\n   \nFood\n-1\n12.50x\n12.50\nLunch\n3\nFood\n0\n')
    assert 'Enter a real calendar date' in first.stdout and 'Category cannot be empty' in first.stdout and first.stdout.count('Enter a positive amount') == 2
    assert 'Expense added successfully. ID: 1' in first.stdout and 'Description: Lunch' in first.stdout
    saved = (p/'expenses.txt').read_text()
    assert '"2024-02-29"' in saved and '"Lunch"' in saved
    second = run(folder, '2\n3\nTravel\n4\n1\n2025-01-01\nTravel\n20\nBus\n0\n')
    assert 'Description: Lunch' in second.stdout and 'No expenses found for that category' in second.stdout and 'Expense updated successfully' in second.stdout
    third = run(folder, '2\n5\n1\n0\n')
    assert 'Description: Bus' in third.stdout and 'deleted successfully' in third.stdout and (p/'expenses.txt').read_text() == ''
    (p/'expenses.txt').write_text('bad record\n')
    bad = run(folder, '1\n2024-01-01\nFood\n1\nTea\n0\n')
    assert 'saving is disabled' in bad.stderr and 'Could not save' in bad.stdout and (p/'expenses.txt').read_text() == 'bad record\n'
    eof = run(folder, '1\n2024-01-01\n')
    assert 'Adding expense cancelled' in eof.stdout
    print('PASS: invalid date, blank category, invalid amounts, and successful search')
    print('PASS: persistence, missing category search, update and reload')
    print('PASS: deletion and empty file')
    print('PASS: malformed file remains unchanged and saving is disabled')
    print('PASS: end of input cancels without looping')
