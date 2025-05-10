#include "Pipe.h"

void CPipe::Render()
{
	if (this->splant != nullptr) splant->Render();
	this->head->Render();
	this->body->Render();
}