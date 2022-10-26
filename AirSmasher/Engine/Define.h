#pragma once

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}			//�f���[�g����
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}		//�����[�X����
#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] p; p = nullptr;}	//�z����f���[�g����