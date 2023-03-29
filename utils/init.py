import os
import datetime
import shutil

parent_dir = os.getcwd()
print(parent_dir)

date = datetime.datetime(2023, 3, 28)

# Create and populate folders
src_path = os.path.join(parent_dir, "utils")
code_path = os.path.join(parent_dir, "code")


# offset >0 to modify folders beyond a given day (if offset = N first day affected is N+1)
offset = 4
date += datetime.timedelta(days=offset)

for i in range(offset,100):
    day_str = "Day"+str(i+1).zfill(3)
    date_str = date.strftime("%d-%m-%y")

    day_path = os.path.join(code_path, "_".join([day_str,date_str]))
    os.mkdir(day_path) # this fails if folder already exists

    for j in range(2):
        challenge_path = os.path.join(day_path, "Challenge"+str(j+1))
        os.mkdir(challenge_path)

        shutil.copyfile(os.path.join(src_path, "template_main.cpp"),
                        os.path.join(challenge_path, "main.cpp"))

        shutil.copyfile(os.path.join(src_path, "template_info.md"),
                        os.path.join(challenge_path, "info.md"))

    date += datetime.timedelta(days=1)
