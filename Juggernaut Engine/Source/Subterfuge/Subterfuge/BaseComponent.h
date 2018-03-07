#pragma once
class BaseComponent
{
public:
	BaseComponent();
	~BaseComponent();

	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void LateUpdate() {};
};

