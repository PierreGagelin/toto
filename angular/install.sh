#!/usr/bin/env bash

sudo apt install nodejs
sudo apt install npm

sudo npm install -g @angular/cli
npm install angular-in-memory-web-api --save

ng new angular-tour-of-heroes

ng generate component heroes
ng generate component hero-detail
ng generate component messages
ng generate component dashboard

ng generate service hero
ng generate service message
ng generate service InMemoryData

ng generate module app-routing --flat --module=app
