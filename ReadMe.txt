Introduction:

This app will help you scrubb any sensitive data from your datical file.

The app will not modify your actual file, instead it will create a scrubbed copy of your file...

The two most common files that would typiclly be used are: daticaldb.log and datical.project
However this app can handle any text file.

-------------------------------------------------------------
useful ideas:

For datical.project use keywords (arguments) like: "hostname" "port" "username" "password"

For daticaldb.log use keywords (arguments) like: "jdbc"
-------------------------------------------------------------
Instructions:

Running the scrubberApp.exe will be done by using a unix based command line(git bash emulator for windows will work just fine).
When in scrubberApp.exe directory, make sure that the file that you would like scrubb is there as well.

It is possible to use as many arguments (keywords to scrubb) as you would like, but the last argument should always be the filename.

The setup of execution structure will look like the following:

scrubberApp.exe keywords="hostname,port,username,password" file=datical.project
	or
datical_log_scrubber.exe keywords="jdbc" file=daticaldb.log
-----------------------------------------------------------------
How to use:

Here is the suggested command line usage for this program:

./scrubberApp.exe hostname port username password datical.project
./scrubberApp.exe jdbc daticaldb.log
