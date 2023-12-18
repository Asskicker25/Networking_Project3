BUILD AND RUN INSTRUCTIONS

1. Open the Networking_Project3.sln under the Networking_Project3 folder.
2. The UDP client and server source code has been linked as STATIC to the other projects.
3. ****So, build the UDP Project first***
4. Once UDP is built, build the Game_Server and Game_Client projects.
5. Copy all the contents in the Extractables folder at the root and paste it in your desired build output folder.
6. Open the Game_Server.exe to run the server.
7. Open upto 4 Game_Client.exe to connect to the server.

USER INPUTS : 

1. W : Move forward in the facing direction.
2. S : Move backward in the facing direction.
3. D : Turn Right 
4. A : Turn Left.
5. Space : Press to FIRE A BULLET when player is active.
6. Space : Press to RESPAWN when player is dead.

Questions : 

1. Protocol : 
	* Have used google protocol buffers to serialize and deserialize messages.
	* Protocol file can be found inside "Networking_Project3\ProtocolFile\MultiplayerProtoBuf.proto".
	* Both the client and server uses the same protocol file. 
	* Protocol is similar to the one mentioned.

2. Game Server : 
	* Have used UDP for connection between Server and Client. 
	* UDP code can be found inside the UDP project of the solution.
	* The Game_Server project uses the "NetworkManager" script to initialize server and it's attributes.
	* 4 clients can be simultaneously connected to the server.
	* Each player is moved only from the input from the client side. 
	* Each bullet is updated in the server and sends updated state to the client.
	* Server reconiliation implemented to receive all packets and update the player states in the server side.
	* void Player::UpdateInput() handles the player movement on server side based on the input received.
	* void NetworkManager::BroadcastToClients() sends all the gamestates to the clients after regular intervals. 
	* BrodcastToClients is only called 5 times per second.
	* The server then sends updated states of player and bullet to the client.

3. Game Client : 
	* Have used UDP for connection. Source code can be found inside UDP project. 
	* The Game Client project uses its own "NetworkManager" to initialize a client.
	* Client Side prediciton implemented. 
	* In the Game_Client project, check the void PlayerManager::PositionPredictor() function for the prediction logic.
	* Reconciliation has been implemented.
	* void NetworkManager::UpdateGameObjectValue() handles client side reconciliation.
	

4. Gameplay : 
	* Player is mvoed around the game through the updates from the server.
	* Player can shoot with the SPACE key.
	* When a player comes in collision with a bullet, the player dies.
	* By pressing SPACE when dead. Player can respawn in it's spawn position.

