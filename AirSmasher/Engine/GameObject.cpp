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

	//KillMe()が呼ばれたら消す
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
	//呼ばれたのが自分なら
	if (objectName_ == childName)
	{
		return this;
	}
	else
	{
		//子供を探す
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

void GameObject::AddCircleCollider(CircleCollider* pCollider)
{
	pCircle_ = pCollider;
}

std::string GameObject::GetObjectName()
{
	return objectName_;
}

//当たり判定
void GameObject::Collision(GameObject* pGameObject)
{
	//自分が呼ばれた　または当たり判定がないとき
	if (this == pGameObject || pGameObject->pCollider_ == nullptr)
	{
		return;
	}
	float x = (transform_.position_.x + pCollider_->GetCenter().x ) - (pGameObject->transform_.position_.x + pGameObject->pCollider_->GetCenter().x);
	float y = (transform_.position_.y + pCollider_->GetCenter().y ) - (pGameObject->transform_.position_.y + pGameObject->pCollider_->GetCenter().y);
	float z = (transform_.position_.z + pCollider_->GetCenter().z ) - (pGameObject->transform_.position_.z + pGameObject->pCollider_->GetCenter().z);
	float radiusSum = pCollider_->GetRadius() + pGameObject->pCollider_->GetRadius();
	//円型同士の当たり判定
	if (x * x + y * y + z * z <= radiusSum * radiusSum)
	{
		OnCollision(pGameObject);
	}
}

void GameObject::CircleCollision(GameObject* pGameObject)
{
	//自分が呼ばれた　または当たり判定がないとき
	if (this == pGameObject || pGameObject->pCircle_ == nullptr)
	{
		return;
	}
	float x = (transform_.position_.x + pCircle_->GetCenter().x) - (pGameObject->transform_.position_.x + pGameObject->pCircle_->GetCenter().x);
	float z = (transform_.position_.z + pCircle_->GetCenter().z) - (pGameObject->transform_.position_.z + pGameObject->pCircle_->GetCenter().z);
	float radiusSum = pCircle_->GetRadius() + pGameObject->pCircle_->GetRadius();
	//円型同士の当たり判定
	if (x * x + z * z <= radiusSum * radiusSum && pCircle_->GetDimension() == pGameObject->pCircle_->GetDimension())
	{
		OnCollision(pGameObject);
	}
	else
	{
		OffCollision(pGameObject);
	}
}

//当たり判定処理
void GameObject::RoundRobin(GameObject* pGameObject)
{
	if (pCollider_ == nullptr && pCircle_ == nullptr)
	{
		return;
	}

	if (pGameObject->pCollider_)
	{
		Collision(pGameObject);
	}

	if (pGameObject->pCircle_)
	{
		CircleCollision(pGameObject);
	}

	for (auto i = pGameObject->childList_.begin(); i != pGameObject->childList_.end(); i++)
	{
		RoundRobin(*i);
	}
}

//オブジェクトの削除
void GameObject::KillMe()
{
	killObject_ = true;
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

//スクリーンの色の変更
void GameObject::SetScreen(int red, int green, int blue)
{
	Direct3D::SetColor((float)red / 255, (float)green / 255, (float)blue / 255);
}