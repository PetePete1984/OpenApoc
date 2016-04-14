
#pragma once

#include "forms/forms.h"
#include "framework/stage.h"

namespace OpenApoc
{

class BaseSelectScreen : public Stage
{
  private:
	sp<Form> menuform;
	StageCmd stageCmd;

  public:
	BaseSelectScreen();
	~BaseSelectScreen();
	// Stage control
	void Begin() override;
	void Pause() override;
	void Resume() override;
	void Finish() override;
	void EventOccurred(Event *e) override;
	void Update(StageCmd *const cmd) override;
	void Render() override;
	bool IsTransition() override;
};
}; // namespace OpenApoc
