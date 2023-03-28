import os
import datetime
import shutil

parent_dir = os.getcwd()
print(parent_dir)

date = datetime.datetime(2023, 3, 28)

# Create and populate folders
src_path = os.path.join(parent_dir, "python_code")

for i in range(100):
    day = "Day"+str(i+1).zfill(3)
    datestr = date.strftime("%d-%m-%y")
    folder = day+"_"+datestr

    day_path = os.path.join(parent_dir, folder)
    os.mkdir(day_path)

    challenge_path = os.path.join(day_path, "Challenge")
    os.mkdir(challenge_path)

    shutil.copyfile(os.path.join(src_path, "template_main.cpp"),
                    os.path.join(challenge_path, "main.cpp"))

    shutil.copyfile(os.path.join(src_path, "template_info.md"),
                    os.path.join(challenge_path, "info.md"))

    date += datetime.timedelta(days=1)
