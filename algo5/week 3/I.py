import re
from collections import defaultdict


def parse_match_line(line, team_goals, player_goals, goal_minutes, team_games, player_games, first_goal_teams, first_goal_players, player_teams):
    match_info, *goals_info = line.split('\n')
    team1, team2, score1, score2 = re.match(r'"(.+)" - "(.+)" (\d+):(\d+)', match_info).groups()
    score1, score2 = map(int, (score1, score2))

    
    team_goals[team1] += score1
    team_goals[team2] += score2

    
    team_games[team1] += 1
    team_games[team2] += 1

    
    min_minute = 91  
    team_first_goal = None
    player_first_goal = None

    
    for i, goal in enumerate(goals_info):
        player, minute = re.match(r'(.+) (\d+)', goal).groups()
        minute = int(minute)
        
        if i < score1:
            player_teams[player] = team1  
        else:
            player_teams[player] = team2  

        
        player_goals[player] += 1
        
        # print(player, minute)
        goal_minutes[player, minute] += 1

        if minute < min_minute:
            min_minute = minute
            team_first_goal = team1 if i < score1 else team2
            player_first_goal = player

    if team_first_goal:
        first_goal_teams[team_first_goal] += 1
    if player_first_goal:
        first_goal_players[player_first_goal] += 1


def total_goals_for(team):
    return team_goals[team]

def mean_goals_per_game_for(team):
    if team_games[team] == 0:
        return 0
    return team_goals[team] / team_games[team]

def total_goals_by(player):
    return player_goals[player]

def mean_goals_per_game_by(player):
    
    games_played = team_games[player_teams[player]]
    if games_played == 0:
        return 0  
    return player_goals[player] / games_played

def goals_on_minute_by(player, minute):
    return goal_minutes[player, minute]

def goals_on_first_minutes_by(player, t):
    return sum(goal_minutes[player, m] for m in range(1, t + 1))

def goals_on_last_minutes_by(player, t):
    return sum(goal_minutes[player, m] for m in range(91 - t, 91))

def score_opens_by_team(team):
    return first_goal_teams[team]

def score_opens_by_player(player):
    return first_goal_players[player]


def process_query(query):
    if query.startswith("Total goals for"):
        team = re.match(r"Total goals for \"(.+)\"", query).group(1)
        return total_goals_for(team)
    elif query.startswith("Mean goals per game for"):
        team = re.match(r"Mean goals per game for \"(.+)\"", query).group(1)
        return mean_goals_per_game_for(team)
    elif query.startswith("Total goals by"):
        player = re.match(r"Total goals by (.+)", query).group(1)
        return total_goals_by(player)
    elif query.startswith("Mean goals per game by"):
        player = re.match(r"Mean goals per game by (.+)", query).group(1)
        return mean_goals_per_game_by(player)
    elif query.startswith("Goals on minute"):
        minute, player = re.match(r"Goals on minute (\d+) by (.+)", query).groups()
        return goals_on_minute_by(player, int(minute))
    elif query.startswith("Goals on first"):
        t, player = re.match(r"Goals on first (\d+) minutes by (.+)", query).groups()
        return goals_on_first_minutes_by(player, int(t))
    elif query.startswith("Goals on last"):
        t, player = re.match(r"Goals on last (\d+) minutes by (.+)", query).groups()
        return goals_on_last_minutes_by(player, int(t))
    elif query.startswith("Score opens by"):
        subject = re.match(r"Score opens by (.+)", query).group(1)
        if '"' in subject:  
            team = subject.strip('"')
            return score_opens_by_team(team)
        else:  
            return score_opens_by_player(subject)




team_goals = defaultdict(int)
player_goals = defaultdict(int)
goal_minutes = defaultdict(int)
team_games = defaultdict(int)
player_games = defaultdict(lambda: set())
first_goal_teams = defaultdict(int)
first_goal_players = defaultdict(int)
player_teams = {}
with open('input.txt', 'r') as file:
    while True:
        line = file.readline().strip()
        if not line:
            break  

        if '-' in line:  
            total_goals = sum(map(int, re.findall(r'\d+', line.split('-')[1])))  
            match_info = line
            for _ in range(total_goals):
                goal_info = file.readline().strip()
                match_info += '\n' + goal_info

            parse_match_line(match_info, team_goals, player_goals, goal_minutes, team_games, player_games, first_goal_teams, first_goal_players, player_teams)
        else:
            # print(line)
            result = process_query(line)
            print(result)
