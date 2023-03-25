#include "Component_Test.h"

#include "Component_InputReader.h"
#include "GameObject.h"

#include "Logging.h"

void Component_Test::Start() {

}

void Component_Test::Update() {
	if (this->game_object->GetComponent<Component_InputReader>()->KeyPressed(DIK_W))
		LOG("pressing W");
}