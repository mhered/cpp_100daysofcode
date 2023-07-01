#link: https://m.youtube.com/watch?v=xPqnoB2hjjA

# Weather App

A sort of real application of threads: consider a super simple weather app where the end user may select a city from a list and get temperature readings.

However, the data is in a remote server located far away and the connection is very slow, say retrieving the data takes 2 seconds for the request to travel to the rserver and 2 seconds for the data to get back. An unacceptable wait for the user!

Instead we will organize our app using three threads:
- one thread `server_worker` will reproduce the remote process that takes temperature measurements and stores them in the remote server. This will simulate random temperature fluctuations at varying intervals to make it more interesting.
- a second thread `retrieval_worker` will run in the background to regularly retrieve temperature data from the server and store it locally. Simulate the 2sec delay to reach the remote server and copy the values from `remote_server` and 2sec for the data to travel back and be copied to a `local_cache`
- execute the user interface in the main thread. This will get a selection from the user to show the temperature of one of the cities in the list, show immediately the locally stored value, then refresh the display regularly whenever this value is updated in `local_cache`.

Loosely inspired by a demo exercise from the video tutorial in the link above.

## Bonus
- Create a vector of `retrieval_worker` threads and launch them at regular intervals to give the impression of quasi real-time temperature updates despite the 4-seconds delay.

# Tags
#tags:

- [x] threads
- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV