

configure_file(index.html index.html COPYONLY)

configure_file(main.ts main.ts COPYONLY)

configure_file(polyfills.ts polyfills.ts COPYONLY)

configure_file(styles.css styles.css COPYONLY)

configure_file(favicon.ico favico.ico COPYONLY)

configure_file(tsconfig.app.json tsconfig.app.json COPYONLY)
configure_file(tsconfig.spec.json tsconfig.spec.json COPYONLY)

add_subdirectory(app)
add_subdirectory(environments)
