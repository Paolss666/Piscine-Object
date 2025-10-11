#ifndef FORM_HPP
#define FORM_HPP

#include "FormType.hpp"

class Form
{
private:
	FormType _formType;

public:
	Form(FormType p_formType);
	virtual ~Form() = default;
	
	FormType formType() const;
	virtual void execute() = 0;
};

class CourseFinishedForm : public Form
{
private:
	// Add necessary attributes for form completion

public:
	CourseFinishedForm();
	void execute() override;
};

class NeedMoreClassRoomForm : public Form
{
private:
	// Add necessary attributes for form completion

public:
	NeedMoreClassRoomForm();
	void execute() override;
};

class NeedCourseCreationForm : public Form
{
private:
	// Add necessary attributes for form completion

public:
	NeedCourseCreationForm();
	void execute() override;
};

class SubscriptionToCourseForm : public Form
{
private:
	// Add necessary attributes for form completion

public:
	SubscriptionToCourseForm();
	void execute() override;
};

#endif