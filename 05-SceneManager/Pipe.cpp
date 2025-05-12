#include "Pipe.h"

void CPipe::Render()
{
	if (this->splant != nullptr) splant->Render();
	if (this->head != nullptr) head->Render();
	this->body->Render();
}