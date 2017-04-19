function [str] = ga2latex(str)

% Set italic to some tokens.
token_format = {'%s' '\\it{%s}\\rm'};
italic = @(str) sprintf(token_format{isnan(str2double(str))+1},str);

% Create the list of regular expressions and related TeX commands.
list = {
    '\\gp'     '\\,'
    '\\igp'    '/'
    '\\inner'  '\\cdot'
    '\\join'   '\\cup'
    '\\lcont'  '\\rfloor'
    '\\meet'   '\\cap'
    '\\op'     '\\wedge'
    '\\rcont'  '\\lfloor'
    '\\scp'    '\\ast'
    '\\delrap' '\\Delta'
    ...
    '\\blade{([a-zA-Z0-9\\ ]+)}{([a-zA-Z0-9\\ ]+)}'   '\\bf{$1}\\rm_{\\langle{${italic($2)}}\\rangle}'
    '\\kvector{([a-zA-Z0-9\\ ]+)}{([a-zA-Z0-9\\ ]+)}' '\\rm{$1}_{\\langle{${italic($2)}}\\rangle}'
    '\\mv{([a-zA-Z0-9\\ ]+)}'                         '\\it{$1}\\rm'
    '\\rotor{([a-zA-Z0-9\\ ]+)}'                      '\\bf{$1}\\rm'
    '\\scalar{([a-zA-Z0-9\\ ]+)}'                     '\\rm{$1}'
    '\\vector{([a-zA-Z0-9\\ ]+)}'                     '\\bf{$1}\\rm'
    '\\vectorei{([a-zA-Z0-9\\ ]+)}'                   '\\bf{e}\\rm_{${italic($1)}}'
    '\\vectorni'                                      '\\bf{\\infty}\\rm'
    '\\vectorno'                                      '\\bf{o}\\rm'
    '\\versor{([a-zA-Z0-9\\ ]+)}'                     '\\bf{$1}\\rm'
    ...
    '\\dual{(.+)}'            '{$1}^{\\ast}'
    '\\inverse{(.+)}'         '{$1}^{-1}'
    '\\inv{(.+)}'             '{$1}^{-1}'
    '\\norm{(.+)}'            '\|{$1}||'
    '\\sqrnorm{(.+)}'         '||{$1}||^{2}'
    '\\takegrade{(.+)}{(.+)}' '\\langle{$1}\\rangle_{$2}'
    '\\undual{(.+)}'          '{$1}^{-\\ast}'};

% Replace tokens.
for i=1:size(list,1)
    str = regexprep(str,list{i,:});
end

% Return resulting TeX command.
str = strcat('$$',str,'$$');