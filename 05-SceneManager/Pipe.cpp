#include "Pipe.h"

void CPipe::Render()
{
	this->head->Render();
	this->body->Render();

	if (this->splant != nullptr) splant->Render();
}