import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

import { Observable, of } from 'rxjs';
import { catchError, map, tap } from 'rxjs/operators';

import { MessageService } from './message.service'

import { Hero } from './hero'

@Injectable({
    providedIn: 'root'
})
export class HeroService {

    private heroesUrl = 'api/heroes';

    private handleError<T>(operation = 'operation', result?: T) {
        return (error: any): Observable<T> => {
            console.error(error);
            this.log(`${operation} failed: ${error.message}`);
            return of(result as T);
        };
    }

    getHeroes(): Observable<Hero[]> {
        return this.http.get<Hero[]>(this.heroesUrl).pipe(
            tap(_ => this.log('fetched hero list')),
            catchError(this.handleError<Hero[]>('getHeroes', [])),
        );
    }

    getHero(id: number): Observable<Hero> {
        const url = `${this.heroesUrl}/${id}`;
        return this.http.get<Hero>(url).pipe(
            tap(_ => this.log(`fetched hero [hero_id=${id}]`)),
            catchError(this.handleError<Hero>(`getHero id=${id}`)),
        );
    }

    private log(message: string) {
        this.messageService.add(`HeroService: ${message}`);
    }

    constructor(
        private messageService: MessageService,
        private http: HttpClient,
    ) { }
}
