import subprocess


proc = subprocess.run(
		["cd", "pa0"],
		capture_output=True
	)
# proc = subprocess.run("cd pa0 && python assignment_autograder.py".split(" "), capture_output=True)

print(proc.stdout)
print(proc.stderr)


