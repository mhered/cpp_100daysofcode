import os
import datetime


# use timedelta to easily adjust the date if needed (e.g. after 23:59)
date_of_today = datetime.date.today()- datetime.timedelta(days=0) 
start_date = datetime.date(2023, 3, 27)

num_of_days = (date_of_today - start_date).days + 1

# Create folders
day = "Day"+str(num_of_days).zfill(3)
datestr = date_of_today.strftime("%d-%m-%y")
folder = day+"_"+datestr

github_root = "https://github.com/mhered/cpp_100daysofcode/blob/main/code/"

code_path = os.path.join(os.getcwd(), "code")
path = os.path.join(code_path, folder)

challenges = next(os.walk(path))[1]  # get list of subfolders

external_links = []
github_links = []
for challenge in challenges:
    readme_file = os.path.join(path, challenge, "README.md")
    github_links.append(os.path.join(github_root, folder, challenge))
    with open(readme_file) as file:  # Use file to refer to the file object
        for line in file:
            if line.rstrip().startswith("#link:"):
                external_links.append(line.split("#link:")[1].strip())


templatetweet = "Day " + str(num_of_days) + \
    ": #100DaysOfCode in #Cpp progress - today "

num_challenges = len(challenges)

if num_challenges > 0:
    connectors = [", "]*(num_challenges)
    if num_challenges == 1:
        connectors[0] = "I worked on the project "
    else:
        connectors[0] = "I worked on the projects "
        connectors[-1] = " and "

    for connector, challenge, external_link, github_link in zip(connectors, challenges, external_links, github_links):
        tmp = connector + challenge + " " + \
            github_link + " (see " + external_link + ")"
        templatetweet += tmp

else:
    templatetweet += "it seems that I took a rest!"

with open("README.md", "a") as file:
    # file.write("\n---\n")
    file.write("\n ## "+datestr+"\n\n")
    file.write(templatetweet)
