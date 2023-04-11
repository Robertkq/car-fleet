#ifndef CAR_FLEET_CPP_MENUS_H
#define CAR_FLEET_CPP_MENUS_H

#include "common.h"

struct Application;

struct base_menu
{
    public:
        base_menu(Application* _parent);
        virtual void show() const = 0;
        virtual ~base_menu();
    protected:
        Application* parent;
};

struct main_menu : public base_menu
{
    public:
        main_menu(Application* _parent);
        virtual void show() const override;
    private:
};

struct view_menu : public base_menu
{
    public:
        view_menu(Application* _parent);
        virtual void show() const override;
    private:
};

struct add_menu : public base_menu
{
    public:
        add_menu(Application* _parent);
        virtual void show() const override;
    private:
};

struct search_menu : public base_menu
{
    public:
        search_menu(Application* _parent);
        virtual void show() const override;
    private:
};

struct detailed_menu : public base_menu
{
    public:
        detailed_menu(Application* _parent);
        virtual void show() const override;
    private:
};

struct edit_menu : public base_menu
{
    public:
        edit_menu(Application* _parent);
        virtual void show() const override;
    private:
};

struct about_menu : public base_menu
{
    public:
        about_menu(Application* _parent);
        virtual void show() const override;
    private:
};

#endif