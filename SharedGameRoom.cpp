#include <iostream>
#include <memory>
#include <string>

class GameRoom 
{
private:
    std::string name;
public:
    GameRoom(const std::string& name) : name(name)
    {
        std::cout << "Game room " << name << " created" << std::endl;
    }
    ~GameRoom() 
    {
        std::cout << "Game room " << name << " destroyed" << std::endl;
    }
    std::string getName()
    {
        return name;
    }
};

class Player 
{
private:
    std::string name;
    std::shared_ptr<GameRoom> gameRoom;

public:
    Player(const std::string& name, std::shared_ptr<GameRoom> gameRoom = nullptr) : name(name)
    {
        if (gameRoom)
            this->gameRoom = gameRoom;
        std::cout << "Player " << name << " created" << std::endl;
    }
    ~Player() 
    {
        std::cout << "Player " << name << " destroyed" << std::endl;
    }

    void joinRoom(std::shared_ptr<GameRoom> room) 
    {
        if (gameRoom) 
        {
            std::cout << "Player " << name << " is already in a room" << std::endl;
            return;
        }
        gameRoom = room;
        std::cout << "Player " << name << " joined room " << room->getName() << std::endl;
    }

    void leaveRoom() 
    {
        if (!gameRoom) 
        {
            std::cout << "Player " << name << " is not in a room" << std::endl;
            return;
        }
        gameRoom.reset();
        std::cout << "Player " << name << " left the room." << std::endl;
    }

    std::shared_ptr<GameRoom> getGameRoom()
    {
        return gameRoom;
    }
};

std::shared_ptr<Player> createPlayer(const std::string& playerName, std::shared_ptr<GameRoom> room = nullptr) 
{
    if (!room)
    {
        room = std::make_shared<GameRoom>("DefaultRoom");
        std::cout << "Player " << playerName << " entered default room" << std::endl;
    }
       
    
    
    return std::make_shared<Player>(playerName, room);
}

int main() 
{
    std::cout << "Create player 1 and join default room" << std::endl;
    std::shared_ptr<Player> player1 = createPlayer("player1");
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "Create player 2 and join player 1 room  (default room)" << std::endl;
    std::shared_ptr<Player> player2 = createPlayer("player2", player1->getGameRoom());
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "Create player 3 and join player 1 room  (default room)" << std::endl;
    std::shared_ptr<Player> player3 = createPlayer("player3", player1->getGameRoom());
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "Player 1-3 leave Default room" << std::endl;
    player1->leaveRoom();
    player2->leaveRoom();
    player3->leaveRoom();
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "Create player 4 and join new room  (GameRoom 2)" << std::endl;
    auto player4 = createPlayer("player4", std::make_shared<GameRoom>("GameRoom 2"));
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "Players 2 and 3 join player 4 room (GameRoom 2)" << std::endl;
    player2->joinRoom(player4->getGameRoom());
    player3->joinRoom(player4->getGameRoom());
    std::cout << "------------------------------------------------------" << std::endl;

    return 0;
}
