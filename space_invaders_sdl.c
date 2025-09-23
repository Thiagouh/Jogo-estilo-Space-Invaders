#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WINDOW_W 800
#define WINDOW_H 600

#define MAX_INV 80
#define MAX_BUL 256
#define PLAYER_BULLET_LIMIT 3

typedef enum { STATE_MENU, STATE_CUSTOMIZE, STATE_DIFFICULTY, STATE_PLAYING, STATE_GAME_OVER, STATE_QUIT } GameState;
typedef struct { float x, y; int alive; int row, col; } GInv;
typedef struct { float x, y; int active; int from_enemy; float vy; } GBullet;
typedef struct { float x, y; int lives; int score; } GPlayer;

GInv ginv[MAX_INV];
GBullet gbul[MAX_BUL];
GPlayer gplayer;

int inv_rows = 5; int inv_cols = 10; int remaining_inv = 0;
float inv_speed = 40.0f; int inv_dir = 1;
float enemy_bullet_speed = 180.0f; float enemy_fire_rate = 0.003f;
SDL_Color player_color = {0, 255, 255, 255};

void spawn_ginv() {
    float startx = 80; float starty = 80; float gapx = 60; float gapy = 50;
    remaining_inv = 0; int idx = 0;
    for (int r = 0; r < inv_rows; r++) {
        for (int c = 0; c < inv_cols; c++) {
            if (idx >= MAX_INV) break;
            ginv[idx].alive = 1; ginv[idx].x = startx + c * gapx; ginv[idx].y = starty + r * gapy;
            ginv[idx].row = r; ginv[idx].col = c; idx++; remaining_inv++;
        }
    }
    for (; idx < MAX_INV; idx++) ginv[idx].alive = 0;
}

void init_gbul() { for (int i = 0; i < MAX_BUL; i++) gbul[i].active = 0; }

int count_player_bullets() {
    int count = 0;
    for (int i = 0; i < MAX_BUL; i++) if (gbul[i].active && !gbul[i].from_enemy) count++;
    return count;
}

void fire_gbul(float x, float y, int from_enemy) {
    if (!from_enemy && count_player_bullets() >= PLAYER_BULLET_LIMIT) return;
    for (int i = 0; i < MAX_BUL; i++) {
        if (!gbul[i].active) {
            gbul[i].active = 1; gbul[i].x = x; gbul[i].y = y;
            gbul[i].from_enemy = from_enemy; gbul[i].vy = from_enemy ? enemy_bullet_speed : -300.0f;
            return;
        }
    }
}

void init_game() {
    srand((unsigned)time(NULL)); gplayer.x = WINDOW_W / 2; gplayer.y = WINDOW_H - 60;
    gplayer.score = 0; inv_rows = 5; inv_cols = 10;
    spawn_ginv(); init_gbul();
}

void draw_player(SDL_Renderer *ren) {
    SDL_SetRenderDrawColor(ren, player_color.r, player_color.g, player_color.b, player_color.a);
    SDL_Point pts[4] = { {(int)gplayer.x, (int)gplayer.y - 14}, {(int)gplayer.x - 14, (int)gplayer.y + 14}, {(int)gplayer.x + 14, (int)gplayer.y + 14}, {(int)gplayer.x, (int)gplayer.y - 14}};
    SDL_RenderDrawLines(ren, pts, 4); SDL_RenderDrawLine(ren, pts[1].x, pts[1].y, pts[2].x, pts[2].y);
}

void draw_invader(SDL_Renderer *ren, float x, float y) {
    SDL_Rect body = {(int)x - 16, (int)y - 10, 32, 20}; SDL_SetRenderDrawColor(ren, 200, 200, 0, 255); SDL_RenderFillRect(ren, &body);
    SDL_Rect cut = {(int)x - 6, (int)y - 4, 12, 8}; SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); SDL_RenderFillRect(ren, &cut);
}

int rect_collide(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
    return !(x1 + w1 < x2 || x1 > x2 + w2 || y1 + h1 < y2 || y1 > y2 + h2);
}

void render_text_in_rect(SDL_Renderer *ren, TTF_Font *font, const char *msg, SDL_Rect rect, SDL_Color color) {
    SDL_Surface *surf = TTF_RenderText_Solid(font, msg, color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { rect.x + (rect.w - surf->w) / 2, rect.y + (rect.h - surf->h) / 2, surf->w, surf->h };
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void render_text_centered(SDL_Renderer *ren, TTF_Font *font, const char *msg, int y, SDL_Color color) {
    SDL_Surface *surf = TTF_RenderText_Solid(font, msg, color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = {WINDOW_W / 2 - surf->w / 2, y, surf->w, surf->h};
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

void render_text_left(SDL_Renderer *ren, TTF_Font *font, const char *msg, int x, int y, SDL_Color color) {
    SDL_Surface *surf = TTF_RenderText_Solid(font, msg, color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = {x, y, surf->w, surf->h};
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    SDL_Window *win = SDL_CreateWindow("Space Invaders SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 28);
    TTF_Font *font_big = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 48);
    if (!font || !font_big) { printf("Erro ao carregar fonte: %s\n", TTF_GetError()); return 1; }

    SDL_Texture *background_texture = NULL;
    SDL_Surface *background_surface = IMG_Load("background-space.png");
    if (background_surface != NULL) {
        background_texture = SDL_CreateTextureFromSurface(ren, background_surface);
        SDL_FreeSurface(background_surface);
    }

    GameState game_state = STATE_MENU;
    SDL_Event e; Uint64 last = 0;
    SDL_Color white = {255, 255, 255, 255}; SDL_Color black = {0, 0, 0, 255};

    while (game_state != STATE_QUIT) {
        switch (game_state) {
        case STATE_MENU: {
            SDL_Rect play_rect = {WINDOW_W / 2 - 200, 200, 400, 50};
            SDL_Rect customize_rect = {WINDOW_W / 2 - 200, 300, 400, 50};
            SDL_Rect quit_rect = {WINDOW_W / 2 - 200, 400, 400, 50};
            while (game_state == STATE_MENU) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) game_state = STATE_QUIT;
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int mx = e.button.x, my = e.button.y;
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &play_rect)) game_state = STATE_DIFFICULTY;
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &customize_rect)) game_state = STATE_CUSTOMIZE;
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &quit_rect)) game_state = STATE_QUIT;
                    }
                    if (e.type == SDL_KEYDOWN) if (e.key.keysym.sym == SDLK_ESCAPE) game_state = STATE_QUIT;
                }
                SDL_RenderClear(ren);
                if (background_texture != NULL) SDL_RenderCopy(ren, background_texture, NULL, NULL); else { SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); SDL_RenderClear(ren); }
                render_text_centered(ren, font_big, "SPACE INVADERS SDL", 50, white);
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
                SDL_RenderDrawRect(ren, &play_rect); SDL_RenderDrawRect(ren, &customize_rect); SDL_RenderDrawRect(ren, &quit_rect);
                render_text_in_rect(ren, font, "JOGAR", play_rect, white);
                render_text_in_rect(ren, font, "PERSONALIZAR NAVE", customize_rect, white);
                render_text_in_rect(ren, font, "SAIR", quit_rect, white);
                SDL_RenderPresent(ren);
            }
        } break;
        case STATE_CUSTOMIZE: {
            SDL_Rect cyan_rect = {WINDOW_W / 2 - 200, 150, 400, 50};
            SDL_Rect red_rect = {WINDOW_W / 2 - 200, 220, 400, 50};
            SDL_Rect green_rect = {WINDOW_W / 2 - 200, 290, 400, 50};
            SDL_Rect magenta_rect = {WINDOW_W / 2 - 200, 360, 400, 50};
            SDL_Rect back_rect = {WINDOW_W / 2 - 200, 450, 400, 50};
            while (game_state == STATE_CUSTOMIZE) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) game_state = STATE_QUIT;
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int mx = e.button.x, my = e.button.y;
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &cyan_rect)) player_color = (SDL_Color){0, 255, 255, 255};
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &red_rect)) player_color = (SDL_Color){255, 0, 0, 255};
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &green_rect)) player_color = (SDL_Color){0, 255, 0, 255};
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &magenta_rect)) player_color = (SDL_Color){255, 0, 255, 255};
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &back_rect)) game_state = STATE_MENU;
                    }
                    if (e.type == SDL_KEYDOWN) if (e.key.keysym.sym == SDLK_ESCAPE) game_state = STATE_MENU;
                }
                SDL_RenderClear(ren);
                if (background_texture != NULL) SDL_RenderCopy(ren, background_texture, NULL, NULL); else { SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); SDL_RenderClear(ren); }
                render_text_centered(ren, font_big, "ESCOLHA A COR DA NAVE", 50, white);
                SDL_SetRenderDrawColor(ren, 0, 255, 255, 255); SDL_RenderFillRect(ren, &cyan_rect);
                SDL_SetRenderDrawColor(ren, 255, 0, 0, 255); SDL_RenderFillRect(ren, &red_rect);
                SDL_SetRenderDrawColor(ren, 0, 255, 0, 255); SDL_RenderFillRect(ren, &green_rect);
                SDL_SetRenderDrawColor(ren, 255, 0, 255, 255); SDL_RenderFillRect(ren, &magenta_rect);
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
                SDL_RenderDrawRect(ren, &cyan_rect); SDL_RenderDrawRect(ren, &red_rect); SDL_RenderDrawRect(ren, &green_rect);
                SDL_RenderDrawRect(ren, &magenta_rect); SDL_RenderDrawRect(ren, &back_rect);
                render_text_in_rect(ren, font, "CIANO", cyan_rect, black);
                render_text_in_rect(ren, font, "VERMELHO", red_rect, white);
                render_text_in_rect(ren, font, "VERDE", green_rect, black);
                render_text_in_rect(ren, font, "MAGENTA", magenta_rect, black);
                render_text_in_rect(ren, font, "VOLTAR", back_rect, white);
                render_text_left(ren, font, "Preview:", WINDOW_W - 180, 250, white);
                gplayer.x = WINDOW_W - 100; gplayer.y = 300;
                draw_player(ren);
                SDL_RenderPresent(ren);
            }
        } break;
        case STATE_DIFFICULTY: {
            SDL_Rect easy = {WINDOW_W / 2 - 200, 150, 400, 50}, med = {WINDOW_W / 2 - 200, 250, 400, 50}, hard = {WINDOW_W / 2 - 200, 350, 400, 50};
            int difficulty = -1;
            while (game_state == STATE_DIFFICULTY) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) game_state = STATE_QUIT;
                    if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_1) difficulty = 0; if (e.key.keysym.sym == SDLK_2) difficulty = 1;
                        if (e.key.keysym.sym == SDLK_3) difficulty = 2; if (e.key.keysym.sym == SDLK_ESCAPE) game_state = STATE_MENU;
                    }
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int mx = e.button.x, my = e.button.y;
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &easy)) difficulty = 0;
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &med)) difficulty = 1;
                        if (SDL_PointInRect(&(SDL_Point){mx, my}, &hard)) difficulty = 2;
                    }
                }
                if (difficulty != -1) {
                    if (difficulty == 0) { gplayer.lives = 5; inv_speed = 25.0f; enemy_bullet_speed = 150.0f; enemy_fire_rate = 0.0015f; }
                    else if (difficulty == 1) { gplayer.lives = 3; inv_speed = 50.0f; enemy_bullet_speed = 250.0f; enemy_fire_rate = 0.0045f; }
                    else { gplayer.lives = 1; inv_speed = 90.0f; enemy_bullet_speed = 370.0f; enemy_fire_rate = 0.010f; }
                    init_game(); game_state = STATE_PLAYING; last = SDL_GetPerformanceCounter();
                }
                SDL_RenderClear(ren);
                if (background_texture != NULL) SDL_RenderCopy(ren, background_texture, NULL, NULL); else { SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); SDL_RenderClear(ren); }
                render_text_centered(ren, font_big, "ESCOLHA A DIFICULDADE", 50, white);
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
                SDL_RenderDrawRect(ren, &easy); SDL_RenderDrawRect(ren, &med); SDL_RenderDrawRect(ren, &hard);
                render_text_in_rect(ren, font, "1 - Facil", easy, white);
                render_text_in_rect(ren, font, "2 - Medio", med, white);
                render_text_in_rect(ren, font, "3 - Dificil", hard, white);
                SDL_RenderPresent(ren);
            }
        } break;
        case STATE_PLAYING: {
            Uint64 now = SDL_GetPerformanceCounter(); float dt = (float)(now - last) / SDL_GetPerformanceFrequency(); last = now;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) game_state = STATE_QUIT;
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) game_state = STATE_MENU;
                    if (e.key.keysym.sym == SDLK_SPACE) fire_gbul(gplayer.x, gplayer.y - 20, 0);
                }
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) gplayer.x -= 300 * dt;
            if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) gplayer.x += 300 * dt;
            if (gplayer.x < 20) gplayer.x = 20; if (gplayer.x > WINDOW_W - 20) gplayer.x = WINDOW_W - 20;
            float minx = 1e9, maxx = -1e9;
            for (int i = 0; i < MAX_INV; i++) if (ginv[i].alive) { if (ginv[i].x < minx) minx = ginv[i].x; if (ginv[i].x > maxx) maxx = ginv[i].x; }
            if (minx < 20 && inv_dir == -1) inv_dir = 1; if (maxx > WINDOW_W - 20 && inv_dir == 1) inv_dir = -1;
            for (int i = 0; i < MAX_INV; i++) if (ginv[i].alive) ginv[i].x += inv_dir * inv_speed * dt;
            for (int c = 0; c < inv_cols; c++) {
                int shooter = -1;
                for (int r = inv_rows - 1; r >= 0; r--) {
                    for (int i = 0; i < MAX_INV; i++) if (ginv[i].alive && ginv[i].row == r && ginv[i].col == c) { shooter = i; break; }
                    if (shooter != -1) break;
                }
                if (shooter != -1) if (((float)rand() / RAND_MAX) < enemy_fire_rate) fire_gbul(ginv[shooter].x, ginv[shooter].y + 20, 1);
            }
            for (int i = 0; i < MAX_BUL; i++) {
                if (!gbul[i].active) continue;
                gbul[i].y += gbul[i].vy * dt;
                if (gbul[i].y < 0 || gbul[i].y > WINDOW_H) { gbul[i].active = 0; continue; }
                if (gbul[i].from_enemy) {
                    if (rect_collide(gbul[i].x - 3, gbul[i].y - 6, 6, 12, gplayer.x - 14, gplayer.y - 14, 28, 28)) {
                        gbul[i].active = 0; gplayer.lives--;
                        if (gplayer.lives <= 0) game_state = STATE_GAME_OVER;
                    }
                } else {
                    for (int j = 0; j < MAX_INV; j++) {
                        if (!ginv[j].alive) continue;
                        if (rect_collide(gbul[i].x - 3, gbul[i].y - 6, 6, 12, ginv[j].x - 16, ginv[j].y - 10, 32, 20)) {
                            gbul[i].active = 0; ginv[j].alive = 0; remaining_inv--; gplayer.score += 10; break;
                        }
                    }
                }
            }
            for (int j = 0; j < MAX_INV; j++) {
                if (!ginv[j].alive) continue;
                if (rect_collide(gplayer.x - 14, gplayer.y - 14, 28, 28, ginv[j].x - 16, ginv[j].y - 10, 32, 20)) {
                    gplayer.lives = 0; game_state = STATE_GAME_OVER;
                }
            }
            static float difficulty_scaling_factor = 1.15f;
            if (gplayer.lives == 5) difficulty_scaling_factor = 1.10f;
            else if (gplayer.lives == 3) difficulty_scaling_factor = 1.15f;
            else if (gplayer.lives == 1) difficulty_scaling_factor = 1.25f;
            if (remaining_inv <= 0) {
                inv_rows = (inv_rows < 8) ? inv_rows + 1 : inv_rows; inv_cols = (inv_cols < 12) ? inv_cols + 1 : inv_cols;
                inv_speed *= difficulty_scaling_factor; spawn_ginv(); init_gbul();
            }
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); SDL_RenderClear(ren);
            for (int i = 0; i < gplayer.lives; i++) {
                SDL_Rect life = {10 + i * 22, 10, 16, 16}; SDL_SetRenderDrawColor(ren, 0, 200, 0, 255); SDL_RenderFillRect(ren, &life);
            }
            draw_player(ren);
            for (int i = 0; i < MAX_INV; i++) if (ginv[i].alive) draw_invader(ren, ginv[i].x, ginv[i].y);
            for (int i = 0; i < MAX_BUL; i++) {
                if (!gbul[i].active) continue;
                SDL_Rect brect = {(int)gbul[i].x - 3, (int)gbul[i].y - 6, 6, 12};
                if (gbul[i].from_enemy) SDL_SetRenderDrawColor(ren, 255, 60, 60, 255); else SDL_SetRenderDrawColor(ren, 60, 255, 60, 255);
                SDL_RenderFillRect(ren, &brect);
            }
            char score_str[50]; sprintf(score_str, "PONTOS: %d", gplayer.score);
            render_text_left(ren, font, score_str, WINDOW_W - 220, 10, white);
            char level_str[50]; sprintf(level_str, "ONDA: %dx%d", inv_rows, inv_cols);
            render_text_left(ren, font, level_str, WINDOW_W - 220, 40, white);
            SDL_RenderPresent(ren);
        } break;
        case STATE_GAME_OVER: {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) game_state = STATE_QUIT;
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_j || e.key.keysym.sym == SDLK_m) game_state = STATE_MENU;
                    if (e.key.keysym.sym == SDLK_ESCAPE) game_state = STATE_QUIT;
                }
            }
            SDL_SetRenderDrawColor(ren, 20, 0, 0, 255); SDL_RenderClear(ren);
            char score_text[100]; sprintf(score_text, "Pontuacao Final: %d", gplayer.score);
            render_text_centered(ren, font_big, "FIM DE JOGO", 150, white);
            render_text_centered(ren, font, score_text, 250, white);
            render_text_centered(ren, font, "Pressione [J] para jogar novamente", 350, white);
            render_text_centered(ren, font, "Pressione [ESC] para sair", 400, white);
            SDL_RenderPresent(ren);
        } break;
        default: break;
        }
    }

    if (background_texture != NULL) SDL_DestroyTexture(background_texture);
    SDL_DestroyRenderer(ren); SDL_DestroyWindow(win);
    TTF_CloseFont(font); TTF_CloseFont(font_big);
    IMG_Quit();
    TTF_Quit(); SDL_Quit(); return 0;
}