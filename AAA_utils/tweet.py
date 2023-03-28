import os
import datetime
  
date_of_today = datetime.date.today()  
start_date=datetime.date(2023,3,28)

num_of_days = (date_of_today - start_date).days +1

# Create folders
day= "Day"+str(num_of_days).zfill(3)
datestr=date_of_today.strftime("%d-%m-%y")
folder=day+"_"+datestr
path = os.path.join(".", folder)

challenges = next(os.walk(path))[1] # get list of subfolders

links =[]
for challenge in challenges:
    info_filename = os.path.join(path, challenge, "info.md")
    with open(info_filename) as file: # Use file to refer to the file object
        for line in file:
            if line.rstrip().startswith("#link:"):
                links.append(line.split("#link:")[1].strip())


templatetweet = "Day " + str(num_of_days) + " #100DaysOfCode #cpp progress: today "

num_challenges = len(challenges)

if num_challenges > 0:
    connectors=[", "]*(num_challenges)
    if num_challenges==1: 
        connectors[0] = "I worked on the following challenge: "
    else:
        connectors[0]="I worked on the following challenges: "
        connectors[-1]=" and "

    for connector, challenge, link in zip(connectors, challenges, links):
        tmp= connector + challenge + " " + link
        templatetweet += tmp

else:
    templatetweet += "it seems that I took a rest!"

print(templatetweet)
