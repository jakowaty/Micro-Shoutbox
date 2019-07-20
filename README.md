# Shoutbox - project C++, PHP, JS

### Module to keep conversation (queue/bufor)

Compile and run executable.
Server will listen on port 25000 (editable in source code).
Each server instance creates file based lock to do not overlap each other.

#

JS script `asynccli.js` can be embedded in previously prepared HTML page
(element selectors must match actual ones). Script sends messages used to retrieve
whole queue (conversation) or send single message.  

  
PHP scripts `client.php` and `service.php` will open socket to server and transfer data sent by user
through JS script and web interface.

  
C++ server consists of `conversation buffer`, `main` where connections are handled
and `servlock` the part where some tool functions are placed. Server can hold up to 1000 strings each 256 bytes long.
#

