#include "Precompiled.h"
using namespace GER::DDD;

GameObject GameObject::Invalid(Math::InvalidHashName);

void GameObject::OnInit()
{
	NativeOnInit();
}

void GameObject::NativeOnInit()
{

}