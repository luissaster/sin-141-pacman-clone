#include "entity.h"

Entity::Entity() {
    moveSpeed = 0;
    entityX = 0;
    entityY = 0;
    entityConvertedY = 0;
    entityConvertedX = 0;
    entityHeight = 0;
    entityWidth = 0;
    entitySize = 0;
    direction = 0;
    moveUp = moveRight = moveDown = moveLeft = false;
    colYCollisionUp = colXCollisionUp = colYCollisionUpNext = colXCollisionUpNext = 0;
    colYCollisionLeft = colXCollisionLeft = colYCollisionLeftNext = colXCollisionLeftNext = 0;
    colYCollisionRight = colXCollisionRight = colYCollisionRightNext = colXCollisionRightNext = 0;
    colYCollisionBottom = colXCollisionBottom = colYCollisionBottomNext = colXCollisionBottomNext = 0;
}
Entity::~Entity() {}
void Entity::calculateEntityPosition() {
    entityConvertedY = entityY / entitySize;
    entityConvertedX = entityX / entitySize;

    colYCollisionUp = ceil(entityY / entitySize);
    colXCollisionUp = entityX / entitySize;
    colYCollisionUpNext = ceil(entityY / entitySize);
    colXCollisionUpNext = ceil(entityX / entitySize);

    colYCollisionLeft = ceil(entityY / entitySize);
    colXCollisionLeft = ceil(entityX / entitySize);
    colYCollisionLeftNext = entityY / entitySize;
    colXCollisionLeftNext = ceil(entityX / entitySize);

    colYCollisionRight = ceil(entityY / entitySize);
    colXCollisionRight = entityX / entitySize;
    colYCollisionRightNext = entityY / entitySize;
    colXCollisionRightNext = entityX / entitySize;

    colYCollisionBottom = entityY / entitySize;
    colXCollisionBottom = ceil(entityX / entitySize);
    colYCollisionBottomNext = entityY / entitySize;
    colXCollisionBottomNext = entityX / entitySize;
}
bool Entity::checkWallCollision(std::vector<std::vector<char>>& map) {
    return map[entityConvertedY][entityConvertedX] != 0;
}
bool Entity::checkEntityCollisionUp(std::vector<std::vector<char>>& map) {
    return map[colYCollisionUp - 1][colXCollisionUp] != '0' && map[colYCollisionUpNext - 1][colXCollisionUpNext] != '0';
}
bool Entity::checkEntityCollisionDown(std::vector<std::vector<char>>& map) {
    return map[colYCollisionBottom + 1][colXCollisionBottom] != '0' && map[colYCollisionBottomNext + 1][colXCollisionBottomNext] != '0';
}
bool Entity::checkEntityCollisionRight(std::vector<std::vector<char>>& map) {
    return map[colYCollisionRight][colXCollisionRight + 1] != '0' && map[colYCollisionRightNext][colXCollisionRightNext + 1] != '0';
}
bool Entity::checkEntityCollisionLeft(std::vector<std::vector<char>>& map) {
    return map[colYCollisionLeft][colXCollisionLeft - 1] != '0' && map[colYCollisionLeftNext][colXCollisionLeftNext - 1] != '0';
}
int Entity::getEntityConvertedX() {
    return entityConvertedX;
}
int Entity::getEntityConvertedY() {
    return entityConvertedY;
}
float Entity::getEntityX() {
    return entityX;
}
float Entity::getEntityY() {
    return entityY;
}
void Entity::setEntityXPosition(float x) {
    entityX = x;
}
void Entity::setEntityYPosition(float y) {
    entityY = y;
}
void Entity::checkEntityMovement(int instruction, std::vector<std::vector<char>>& map) {
    if (instruction == ALLEGRO_KEY_UP && checkEntityCollisionUp(map)) {
        moveUp = true;
        moveDown = false;
        moveLeft = false;
        moveRight = false;
        direction = 3;
    }
    if (instruction == ALLEGRO_KEY_DOWN && checkEntityCollisionDown(map)) {
        moveDown = true;
        moveUp = false;
        moveLeft = false;
        moveRight = false;
        direction = 1;
    }
    if (instruction == ALLEGRO_KEY_LEFT && checkEntityCollisionLeft(map)) {
        moveLeft = true;
        moveUp = false;
        moveDown = false;
        moveRight = false;
        direction = 2;
    }
    if (instruction == ALLEGRO_KEY_RIGHT && checkEntityCollisionRight(map)) {
        moveRight = true;
        moveUp = false;
        moveDown = false;
        moveLeft = false;
        direction = 0;
    }
}
void Entity::moveEntity(std::vector<std::vector<char>>& map, ALLEGRO_SAMPLE* chomp) {
    al_play_sample(chomp, 0.08, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    if (moveUp && checkEntityCollisionUp(map)) {
        setEntityYPosition(getEntityY() - moveSpeed);
    }
    if (moveDown && checkEntityCollisionDown(map)) {
        setEntityYPosition(getEntityY() + moveSpeed);
    }
    if (moveLeft && checkEntityCollisionLeft(map)) {
        setEntityXPosition(getEntityX() - moveSpeed);
    }
    if (moveRight && checkEntityCollisionRight(map)) {
        setEntityXPosition(getEntityX() + moveSpeed);
    }
    calculateEntityPosition();
}
void Entity::checkTeleportCollisionLeft(std::vector<std::vector<char>>& map) {
    if (getEntityConvertedY() == 9 && getEntityConvertedX() == 0 && moveLeft == true) {
        this->setEntityXPosition(576);
        this->setEntityYPosition(288);
        moveLeft = true;
        moveRight = false;
        moveUp = false;
        moveDown = false;
    }
}
void Entity::checkTeleportCollisionRight(std::vector<std::vector<char>>& map) {
    if (getEntityConvertedY() == 9 && getEntityConvertedX() == 17 && moveRight == true) {
        this->setEntityXPosition(0);
        this->setEntityYPosition(288);
        moveLeft = false;
        moveRight = true;
        moveUp = false;
        moveDown = false;
    }
}