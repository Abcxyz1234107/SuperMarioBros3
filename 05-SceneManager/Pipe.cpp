#include "Pipe.h"

void CPipe::Render()
{
	this->head->Render();
	this->body->Render();
}