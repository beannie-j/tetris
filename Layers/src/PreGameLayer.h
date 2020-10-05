#pragma once

#include "Layer.h"
#include "../../util/src/TextBox.h"
#include "../../util/src/Button.h"

#include <memory>

class PreGameLayer : public Layer
{
public:
	virtual void OnInit() override;
	virtual void OnShutdown() override;

	virtual void OnUpdate() override;
	virtual void OnEvent(sf::Event& event) override;
private:
	std::unique_ptr<TextBox> m_TextBox;
	std::unique_ptr<Button> m_PlayButton;
	std::unique_ptr<Button> m_BackButton;
};

