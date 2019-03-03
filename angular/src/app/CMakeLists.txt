

configure_file(app.component.html app.component.html COPYONLY)
configure_file(app.component.css app.component.css COPYONLY)
configure_file(app.component.ts app.component.ts COPYONLY)
configure_file(app.component.spec.ts app.component.spec.ts COPYONLY)

configure_file(app.module.ts app.module.ts COPYONLY)

configure_file(app-routing.module.ts app-routing.module.ts COPYONLY)

configure_file(hero.service.ts hero.service.ts COPYONLY)
configure_file(hero.service.spec.ts hero.service.spec.ts COPYONLY)

configure_file(message.service.ts message.service.ts COPYONLY)
configure_file(message.service.spec.ts message.service.spec.ts COPYONLY)

configure_file(in-memory-data.service.ts in-memory-data.service.ts COPYONLY)
configure_file(in-memory-data.service.spec.ts in-memory-data.service.spec.ts COPYONLY)

configure_file(hero.ts hero.ts COPYONLY)

add_subdirectory(dashboard)
add_subdirectory(hero-detail)
add_subdirectory(heroes)
add_subdirectory(messages)
