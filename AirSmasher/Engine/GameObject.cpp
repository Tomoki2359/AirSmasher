#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :
	killObject_(false),
	pParent_(parent),
	objectName_(name),
	pCollider_(nullptr)
{
	if (parent)
		transform_.pTransform_ = &parent->transform_;
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub()
{
	Update();
	RoundRobin(GetRootJob());
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	//KillMe()���Ă΂ꂽ�����
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->killObject_ == true)
		{
			(*itr)->ReleaseSub();
			SAFE_RELEASE((*itr));
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}


	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
		SAFE_DELETE(*itr);
	}
	Release();
}

GameObject* GameObject::FindChildObject(std::string childName)
{
	//�Ă΂ꂽ�̂������Ȃ�
	if (objectName_ == childName)
	{
		return this;
	}
	else
	{
		//�q����T��
		for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		{
			GameObject* obj = (*itr)->FindChildObject(childName);
			if (obj != nullptr)
			{
				return obj;
			}
		}
	}
	return nullptr;
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;
	}
	else
	{
		return pParent_->GetRootJob();
	}
}

GameObject* GameObject::FindObject(std::string childName)
{
	return GetRootJob()->FindChildObject(childName);
}

void GameObject::KillAllChildren()
{
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		(*itr)->ReleaseSub();
		SAFE_RELEASE((*itr));
		itr = childList_.erase(itr);
	}
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

std::string GameObject::GetObjectName()
{
	return objectName_;
}

//�����蔻��
void GameObject::Collision(GameObject* pGameObject)
{
	//�������Ă΂ꂽ�@�܂��͓����蔻�肪�Ȃ��Ƃ�
	if (this == pGameObject || pGameObject->pCollider_ == nullptr)
	{
		return;
	}
	float x = (transform_.position_.x + pCollider_->GetCenter_().x ) - (pGameObject->transform_.position_.x + pGameObject->pCollider_->GetCenter_().x);
	float y = (transform_.position_.y + pCollider_->GetCenter_().y ) - (pGameObject->transform_.position_.y + pGameObject->pCollider_->GetCenter_().y);
	float z = (transform_.position_.z + pCollider_->GetCenter_().z ) - (pGameObject->transform_.position_.z + pGameObject->pCollider_->GetCenter_().z);
	float radiusSum = pCollider_->GetRadius() + pGameObject->pCollider_->GetRadius();
	//�~�^���m�̓����蔻��
	if (x * x + y * y + z * z <= radiusSum * radiusSum)
	{
		OnCollision(pGameObject);
	}
}

//�����蔻�菈��
void GameObject::RoundRobin(GameObject* pGameObject)
{
	if (pCollider_ == nullptr)
	{
		return;
	}

	if (pGameObject->pCollider_)
	{
		Collision(pGameObject);
	}

	for (auto i = pGameObject->childList_.begin(); i != pGameObject->childList_.end(); i++)
	{
		RoundRobin(*i);
	}
}

//�I�u�W�F�N�g�̍폜
void GameObject::KillMe()
{
	killObject_ = true;
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

//�X�N���[���̐F�̕ύX
void GameObject::SetScreen(int red, int green, int blue)
{
	Direct3D::SetColor((float)red / 255, (float)green / 255, (float)blue / 255);
}