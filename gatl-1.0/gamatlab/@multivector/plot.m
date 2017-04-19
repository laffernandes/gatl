function [hp] = plot(m,varargin)

% Set the default value for some properties.
grade_color = [ ...
      0   0   0;      % Grade 0 - It is not suppose to be plotted.
    255  20   0;      % Grade 1 - Red.
     40  94 160;      % Grade 2 - Blue.
     96 120  48;      % Grade 3 - Green.
    248 100   0;      % Grade 4 - Orange.
      0   0   0]/255; % Grade 5 and higher - It is not suppose to be plotted.

marker_style = 'o';
marker_size = 3;

line_style = '-';
free_line_style = '--';
tangent_line_style = '-.';
line_width = 1;

arrow_tip_length = [0.08 0.05 0.05];

face_alpha = 0.2;

point_ticks = 'none';
point_ticks_color = [0.5 0.5 0.5];

text = '';
text_offset = zeros(32,1);

offset = zeros(32,1);
resolution = 36;
bivector_orientation = true;

tolerance = ga_tolerance;

% Determine where to draw graphics objects.
newplot(gca);

bounds = [get(gca,'XLim');get(gca,'YLim');get(gca,'ZLim')];
limit_mode_auto = [(strcmp(get(gca,'XLimMode'),'auto') && strcmp(get(gca,'YLimMode'),'auto')) strcmp(get(gca,'ZLimMode'),'auto')];

% Filter plot options.
line_argin = {};
arrow_tip_argin = {};
patch_argin = {};
text_argin = {};
group_argin = {};
for i=1:2:length(varargin)
    switch lower(varargin{i})
        % Tolerance property.
        case 'tolerance'
            if ~(isscalar(varargin{i+1}) && isnumeric(varargin{i+1}) && isreal(varargin{i+1}) && (varargin{i+1} > 0))
                error('GAToolbox:InputArgumentsCheck','Tolerance must be a positive real value.')
            end
            tolerance = varargin{i+1};
        % Offset property.
        case 'offset'
            if ~(isvector(varargin{i+1}) && isnumeric(varargin{i+1}) && isreal(varargin{i+1}))
                error('GAToolbox:InputArgumentsCheck','Offset must be an array of real numbers.')
            end
            offset(1:length(varargin{i+1})) = varargin{i+1};
        % Resolution property.
        case 'resolution'
            if ~(isscalar(varargin{i+1}) && isnumeric(varargin{i+1}) && isreal(varargin{i+1}) && (varargin{i+1} > 0))
                error('GAToolbox:InputArgumentsCheck','Resolution must be a positive integer value.')
            end
            resolution = varargin{i+1};
        % ArrowTipLength
        case 'arrowtiplength'
            if ~(isnumeric(varargin{i+1}) && isreal(varargin{i+1}) && (1 <= numel(varargin{i+1})) && (numel(varargin{i+1}) <= 3))
                error('GAToolbox:InputArgumentsCheck','ArrowTipLength must be a an array of one, two or three real numbers.')
            end
            arrow_tip_length = zeros(3,1);
            arrow_tip_length(1:numel(varargin{i+1})) = reshape(varargin{i+1},numel(varargin{i+1}),1);
        % BivectorOrientation property.
        case 'bivectororientation'
            if ~((isscalar(varargin{i+1}) && islogical(varargin{i+1})) || (((size(varargin{i+1},1) == 1) && ischar(varargin{i+1})) && (strcmpi(varargin{i+1},'true') || strcmpi(varargin{i+1},'false'))))
                error('GAToolbox:InputArgumentsCheck','BivectorOrientation must be ''true'' or ''false''.')
            end
            
            if islogical(varargin{i+1})
                bivector_orientation = varargin{i+1};
            else
                bivector_orientation = strcmpi(varargin{i+1},'true');
            end
        % PointTicks property.
        case 'pointticks'
            if ~(ischar(varargin{i+1}) && (strcmpi(varargin{i+1},'none') || strcmpi(varargin{i+1},'orthographic') || strcmpi(varargin{i+1},'origin')))
                error('GAToolbox:InputArgumentsCheck','PointTicks must be ''none'', ''orthographic'' or ''origin''.')
            end
            point_ticks = varargin{i+1};
        % PointTicksColor property.
        case 'pointtickscolor'
            if ~(isvector(varargin{i+1}) && numel(varargin{i+1})==3 && isnumeric(varargin{i+1}) && isreal(varargin{i+1}))
                error('GAToolbox:InputArgumentsCheck','PointTicksColor must be some RGB value.')
            end
            point_ticks_color = reshape(varargin{i+1},1,3);
        % Text property.
        case 'text'
            if ~ischar(varargin{i+1})
                error('GAToolbox:InputArgumentsCheck','Text must be some array of chars.')
            end
            text = ga2latex(varargin{i+1});
        % Text property.
        case 'textoffset'
            if ~(isvector(varargin{i+1}) && isnumeric(varargin{i+1}) && isreal(varargin{i+1}))
                error('GAToolbox:InputArgumentsCheck','TextOffset must be an array of real numbers.')
            end
            text_offset(1:length(varargin{i+1})) = varargin{i+1};
        % Alpha changes all the alpha properties.
        case 'alpha'
            patch_argin = cat(2,patch_argin,'EdgeAlpha',varargin{i+1},'FaceAlpha',varargin{i+1});
        % Color changes all the color properties.
        case 'color'
            line_argin = cat(2,line_argin,'Color',varargin{i+1},'MarkerEdgeColor',varargin{i+1},'MarkerFaceColor',varargin{i+1});
            patch_argin = cat(2,patch_argin,'EdgeColor',varargin{i+1},'FaceColor',varargin{i+1},'MarkerEdgeColor',varargin{i+1},'MarkerFaceColor',varargin{i+1});
            arrow_tip_argin = cat(2,arrow_tip_argin,'EdgeColor',varargin{i+1},'FaceColor',varargin{i+1},'MarkerEdgeColor',varargin{i+1},'MarkerFaceColor',varargin{i+1});
            text_argin = cat(2,text_argin,'Color',varargin{i+1});
        % EdgeColor changes the color of the line, too.
        case 'edgecolor'
            line_argin = cat(2,line_argin,'Color',varargin{i+1});
            patch_argin = cat(2,patch_argin,'EdgeColor',varargin{i+1});
            arrow_tip_argin = cat(2,arrow_tip_argin,'EdgeColor',varargin{i+1},'FaceColor',varargin{i+1},'MarkerEdgeColor',varargin{i+1},'MarkerFaceColor',varargin{i+1});
        % FontColor and TextColor changes the color of the text, too.
        case {'fontcolor','textcolor'}
            text_argin = cat(2,text_argin,'Color',varargin{i+1});
        % Patch properties only.
        case {'alphadatamapping','ambientstrength','backfacelighting','cdata','cdatamapping','diffusestrength','edgealpha','edgecolor','edgelighting','facealpha','facecolor','facelighting','faces','facevertexalphadata','facevertexcdata','normalmode','specularcolorreflectance','specularexponent','specularstrength','vertexnormals','vertices'}
            patch_argin = cat(2,patch_argin,varargin{i},varargin{i+1});
        % Text properties only.
        case {'fontsize','horizontalalignment','verticalalignment'}
            text_argin = cat(2,text_argin,varargin{i},varargin{i+1});
        % Group properties.
        case {'beingdeleted','busyaction','buttondownfcn','children','clipping','createfcn','deletefcn','erasemode','handlevisibility','hittest','interruptible','parent','selected','selectionhighlight','tag','type','uicontextmenu','userdata','visible'}
            group_argin = cat(2,group_argin,varargin{i},varargin{i+1});
        % Line and patch common properties.
        otherwise
            line_argin = cat(2,line_argin,varargin{i},varargin{i+1});
            patch_argin = cat(2,patch_argin,varargin{i},varargin{i+1});
            arrow_tip_argin = cat(2,arrow_tip_argin,varargin{i},varargin{i+1});
    end
end

% Parse multivectors.
objects = interpret(m,tolerance); if ~iscell(objects), objects = num2cell(objects); end
default_colors = arrayfun(@(index)grade_color(index,:),min(max(double(grade(m)),0),size(grade_color,1))+1,'UniformOutput',false);

% Plot geometric interpretation of multivectors.
r = zeros(size(objects));

plot_type = get(gca,'UserData');
if ischar(plot_type) && strcmp(plot_type,'ga2h_axis')
    % Check geometric algebra model.
    if ~strcmp(model(m),'ga2h')
        error('GAToolbox:InvalidPlot','The current axis is defined only for elements of homogeneous model of 2D space.')
    end

    % Use 2D homogeneous space plot.
    origin = [0;0;0];
    for i=1:numel(objects)
        curr = objects{i};
        curr_color = default_colors{i};

        % Call plot operation.
        switch curr.type
            % Vector.
            case 'vector'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_vector(resolution,arrow_tip_length,curr.weight,[curr.direction;0],offset(1:size(curr.direction,1)+1,1),text,text_offset(1:size(curr.direction,1)+1,1),line_args,head_args,text_args,group_argin);
            % Bivector.
            case 'bivector'
                text_args = {'Color',curr_color,text_argin{:}};
                plane_args = {'LineStyle',line_style,'LineWidth',line_width,'EdgeColor',curr_color,'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none'};
                arrow_line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                arrow_tip_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_bivector(resolution,bivector_orientation,arrow_tip_length,curr.weight,[curr.direction;0 0],offset(1:size(curr.direction,1)+1,1),text,text_offset(1:size(curr.direction,1)+1,1),plane_args,arrow_line_args,arrow_tip_args,text_args,group_argin);
            % Point.
            case 'point'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',':','LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                segment_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                point_args = {'Marker',marker_style,'MarkerSize',marker_size,'MarkerEdgeColor',curr_color,'MarkerFaceColor',curr_color,line_argin{:}};
                r(i) = hggroup(group_argin{:});
                location = [curr.location;1];
                direction = location/norm(location);
                plot_line(limit_mode_auto,bounds,direction,origin,'',zeros(size(location)),line_args,text_args,{'Parent',r(i)});
                plot_vector(resolution,arrow_tip_length,curr.weight,direction,origin,'',zeros(size(location)),segment_args,head_args,text_args,{'Parent',r(i)});
                plot_point(location,point_ticks,point_ticks_color,text,text_offset(1:size(location,1),1),point_args,text_args,{'Parent',r(i)});
            % Line.
            case 'line'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                patch_args = {'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none','LineStyle','none'};
                r(i) = hggroup(group_argin{:});
                location = [curr.location;1];
                direction1 = [curr.direction;0];
                direction2 = location/norm(location);
                plot_plane(limit_mode_auto,bounds,[direction1 direction2],location,'',zeros(size(location)),patch_args,text_args,{'Parent',r(i)});
                plot_line(limit_mode_auto,bounds,direction1,location,text,text_offset(1:size(location,1),1),line_args,text_args,{'Parent',r(i)});
            % Unknown.
            otherwise
                r(i) = NaN;
                warning('GAToolbox:UndefinedPlot','Plot function is not defined for multivectors of type ''%s''.',curr.type)
        end
    end

elseif ischar(plot_type) && strcmp(plot_type,'ga2c_axis')
    % Check geometric algebra model.
    if ~strcmp(model(m),'ga2c') && ~strcmp(model(m),'ga2cv')
        error('GAToolbox:InvalidPlot','The current axis is defined only for elements of conformal model of 2D space.')
    end

    % Use 2D conformal space plot.
    for i=1:numel(objects)
        curr = objects{i};
        curr_color = default_colors{i};

        % Call plot operation.
        switch curr.type
            % Basis vector.
            case 'free_nvector'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_vector(resolution,arrow_tip_length,curr.weight,[0;0;1],offset(1:size(curr.direction,1)+1,1),text,text_offset(1:size(curr.direction,1)+1,1),line_args,head_args,text_args,group_argin);
            % Vector like.
            case 'vector'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_vector(resolution,arrow_tip_length,curr.weight,[curr.direction;0],offset(1:size(curr.direction,1)+1,1),text,text_offset(1:size(curr.direction,1)+1,1),line_args,head_args,text_args,group_argin);
            case 'free_vector'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',free_line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_vector(resolution,arrow_tip_length,curr.weight,[curr.direction;0],offset(1:size(curr.direction,1)+1,1),text,text_offset(1:size(curr.direction,1)+1,1),line_args,head_args,text_args,group_argin);
            case 'tangent_vector'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',tangent_line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                point_args = {'Marker',marker_style,'MarkerSize',marker_size,'MarkerEdgeColor',curr_color,'MarkerFaceColor',curr_color,line_argin{:}};
                segment_args = {'LineStyle',':','LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = hggroup(group_argin{:});
                location_parab = [curr.location;sum(curr.location.^2)];
                direction_parab = cross(cross([curr.direction;0],[0;0;1]),[2*curr.location;-1]);
                location = [curr.location;0];
                plot_vector(resolution,arrow_tip_length,sum(curr.location.^2),[0;0;1],location,'',zeros(size(location)),segment_args,head_args,text_args,{'Parent',r(i)});
                plot_point(location_parab,point_ticks,point_ticks_color,text,text_offset(1:size(location_parab,1),1),point_args,text_args,{'Parent',r(i)});
                plot_vector(resolution,arrow_tip_length,curr.weight,direction_parab/sqrt(sum(direction_parab.^2)),location_parab,'',zeros(size(curr.direction,1)+1,1),line_args,head_args,text_args,{'Parent',r(i)});
                plot_vector(resolution,arrow_tip_length,curr.weight,[curr.direction;0],location,'',zeros(size(curr.direction,1)+1,1),line_args,head_args,text_args,{'Parent',r(i)});
            % Bivector like.
            case 'bivector'
                text_args = {'Color',curr_color,text_argin{:}};
                plane_args = {'LineStyle',line_style,'LineWidth',line_width,'EdgeColor',curr_color,'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none'};
                arrow_line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                arrow_tip_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_bivector(resolution,bivector_orientation,arrow_tip_length,curr.weight,[curr.direction;0 0],offset(1:size(curr.direction,1)+1,1),text,text_offset(1:size(curr.direction,1)+1,1),plane_args,arrow_line_args,arrow_tip_args,text_args,group_argin);
            case 'free_bivector'
                text_args = {'Color',curr_color,text_argin{:}};
                plane_args = {'LineStyle',free_line_style,'LineWidth',line_width,'EdgeColor',curr_color,'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none'};
                arrow_line_args = {'LineStyle',free_line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                arrow_tip_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_bivector(resolution,bivector_orientation,arrow_tip_length,curr.weight,[curr.direction;0 0],offset(1:size(curr.direction,1)+1,1),text,text_offset(1:size(curr.direction,1)+1,1),plane_args,arrow_line_args,arrow_tip_args,text_args,group_argin);
            case 'tangent_bivector'
                text_args = {'Color',curr_color,text_argin{:}};
                plane_args = {'LineStyle',tangent_line_style,'LineWidth',line_width,'EdgeColor',curr_color,'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none'};
                arrow_line_args = {'LineStyle',tangent_line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                arrow_tip_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                location_parab = [curr.location;sum(curr.location.^2)];
                normal = [2*curr.location;-1];
                direction1 = cross(normal,[curr.direction(:,1);0]);
                direction2 = cross(normal,[curr.direction(:,2);0]);
                r(i) = plot_bivector(resolution,bivector_orientation,arrow_tip_length,curr.weight,[direction1/norm(direction1) direction2/norm(direction2)],location_parab,text,text_offset(1:size(direction1,1),1),plane_args,arrow_line_args,arrow_tip_args,text_args,group_argin);
            % Point like.
            case 'point'
                text_args = {'Color',curr_color,text_argin{:}};
                point_args = {'Marker',marker_style,'MarkerSize',marker_size,'MarkerEdgeColor',curr_color,'MarkerFaceColor',curr_color,line_argin{:}};
                segment_args = {'LineStyle',':','LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = hggroup(group_argin{:});
                location = [curr.location;0];
                location_parab = [curr.location;sum(curr.location.^2)];
                plot_vector(resolution,arrow_tip_length,sum(curr.location.^2),[0;0;1],location,'',zeros(size(location)),segment_args,head_args,text_args,{'Parent',r(i)});
                plot_point(location,point_ticks,point_ticks_color,'',zeros(size(location)),point_args,text_args,{'Parent',r(i)});
                plot_point(location_parab,point_ticks,point_ticks_color,text,text_offset(1:size(location_parab,1),1),point_args,text_args,{'Parent',r(i)});
            case 'flat_point'
                text_args = {'Color',curr_color,text_argin{:}};
                point_args = {'Marker',marker_style,'MarkerSize',marker_size,'MarkerEdgeColor',curr_color,'MarkerFaceColor',curr_color,line_argin{:}};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                r(i) = hggroup(group_argin{:});
                location = [curr.location;0];
                location_parab = [curr.location;sum(curr.location.^2)];
                plot_line(limit_mode_auto,bounds,[0;0;1],location,'',zeros(size(location)),line_args,text_args,{'Parent',r(i)});
                plot_point(location,point_ticks,point_ticks_color,'',zeros(size(location)),point_args,text_args,{'Parent',r(i)});
                plot_point(location_parab,point_ticks,point_ticks_color,text,text_offset(1:size(location_parab,1),1),point_args,text_args,{'Parent',r(i)});
            case 'point_pair'
                text_args = {'Color',curr_color,text_argin{:}};
                point_args = {'Marker',marker_style,'MarkerSize',marker_size,'MarkerEdgeColor',curr_color,'MarkerFaceColor',curr_color,line_argin{:}};
                segment_args = {'LineStyle',':','LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                r(i) = hggroup(group_argin{:});
                location1 = [curr.p1;0];
                location2 = [curr.p2;0];
                location1_parab = [curr.p1;sum(curr.p1.^2)];
                location2_parab = [curr.p2;sum(curr.p2.^2)];
                plot_line(limit_mode_auto,bounds,(location2_parab-location1_parab)/norm(location2_parab-location1_parab),location1_parab,'',zeros(size(location1_parab)),line_args,text_args,{'Parent',r(i)});
                plot_vector(resolution,arrow_tip_length,location1_parab(3),[0;0;-1],location1_parab,'',zeros(size(location1_parab)),segment_args,head_args,text_args,{'Parent',r(i)});
                plot_vector(resolution,arrow_tip_length,location2_parab(3),[0;0;-1],location2_parab,'',zeros(size(location2_parab)),segment_args,head_args,text_args,{'Parent',r(i)});
                plot_point_pair(location1,location2,point_ticks,point_ticks_color,'',zeros(size(location1)),point_args,text_args,{'Parent',r(i)});
                plot_point_pair(location1_parab,location2_parab,point_ticks,point_ticks_color,text,text_offset(1:size(location1_parab,1),1),point_args,text_args,{'Parent',r(i)});
            % Line.
            case 'line'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                patch_args = {'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none','LineStyle','none'};
                r(i) = hggroup(group_argin{:});
                plot_plane(limit_mode_auto,bounds,[[curr.direction;0] [0;0;1]],[curr.location;0],text,text_offset(1:size(curr.direction,1)+1,1),patch_args,text_args,{'Parent',r(i)});
                plot_line_parabola(resolution,limit_mode_auto,bounds,curr.direction,curr.location,line_args,{'Parent',r(i)});
            % Circle.
            case 'circle'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                patch_args = {'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none','LineStyle','none'};
                r(i) = hggroup(group_argin{:});
                point1 = curr.location+curr.radius*curr.direction(:,1);
                point1 = cat(1,point1,sum(point1.^2));
                point2 = curr.location+curr.radius*curr.direction(:,2);
                point2 = cat(1,point2,sum(point2.^2));
                point3 = curr.location+curr.radius*-curr.direction(:,2);
                point3 = cat(1,point3,sum(point3.^2));

                warning('Remover isso depois. Foi colocado para o paper.')
                point1(3) = sign(curr.radius)*point1(3);
                point2(3) = sign(curr.radius)*point2(3);
                point3(3) = sign(curr.radius)*point3(3);
                
                direction1 = (point2-point1)/norm(point2-point1);
                direction2 = (point3-point1)/norm((point3-point1));
                
                plot_plane(limit_mode_auto,bounds,[direction1 direction2],point1,text,text_offset(1:size(point1,1),1),patch_args,text_args,{'Parent',r(i)});
                plot_circle_parabola(resolution,bounds,curr.location,curr.radius,line_args,{'Parent',r(i)});
            % Unknown.
            otherwise
                r(i) = NaN;
                warning('GAToolbox:UndefinedPlot','Plot function is not defined for multivectors of type ''%s''.',curr.type)
        end
    end

else
    % Use simple plot.
    for i=1:numel(objects)
        curr = objects{i};
        curr_color = default_colors{i};

        % Call plot operation.
        switch curr.type
            % Vector like.
            case 'vector'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_vector(resolution,arrow_tip_length,curr.weight,curr.direction,offset(1:size(curr.direction,1),1),text,text_offset(1:size(curr.direction,1),1),line_args,head_args,text_args,group_argin);
            case 'free_vector'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',free_line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_vector(resolution,arrow_tip_length,curr.weight,curr.direction,offset(1:size(curr.direction,1),1),text,text_offset(1:size(curr.direction,1),1),line_args,head_args,text_args,group_argin);
            case 'tangent_vector'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',tangent_line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                head_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_vector(resolution,arrow_tip_length,curr.weight,curr.direction,curr.location,text,text_offset(1:size(curr.direction,1),1),line_args,head_args,text_args,group_argin);
            % Bivector like.
            case 'bivector'
                text_args = {'Color',curr_color,text_argin{:}};
                plane_args = {'LineStyle',line_style,'LineWidth',line_width,'EdgeColor',curr_color,'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none'};
                arrow_line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                arrow_tip_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_bivector(resolution,bivector_orientation,arrow_tip_length,curr.weight,curr.direction,offset(1:size(curr.direction,1),1),text,text_offset(1:size(curr.direction,1),1),plane_args,arrow_line_args,arrow_tip_args,text_args,group_argin);
            case 'free_bivector'
                text_args = {'Color',curr_color,text_argin{:}};
                plane_args = {'LineStyle',free_line_style,'LineWidth',line_width,'EdgeColor',curr_color,'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none'};
                arrow_line_args = {'LineStyle',free_line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                arrow_tip_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_bivector(resolution,bivector_orientation,arrow_tip_length,curr.weight,curr.direction,offset(1:size(curr.direction,1),1),text,text_offset(1:size(curr.direction,1),1),plane_args,arrow_line_args,arrow_tip_args,text_args,group_argin);
            case 'tangent_bivector'
                text_args = {'Color',curr_color,text_argin{:}};
                plane_args = {'LineStyle',tangent_line_style,'LineWidth',line_width,'EdgeColor',curr_color,'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none'};
                arrow_line_args = {'LineStyle',tangent_line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                arrow_tip_args = {'FaceColor',curr_color,arrow_tip_argin{:},'FaceAlpha',1,'Marker','none','LineStyle','none'};
                r(i) = plot_bivector(resolution,bivector_orientation,arrow_tip_length,curr.weight,curr.direction,curr.location,text,text_offset(1:size(curr.direction,1),1),plane_args,arrow_line_args,arrow_tip_args,text_args,group_argin);
            % Point like.
            case {'point','flat_point'}
                text_args = {'Color',curr_color,text_argin{:}};
                point_args = {'Marker',marker_style,'MarkerSize',marker_size,'MarkerEdgeColor',curr_color,'MarkerFaceColor',curr_color,line_argin{:}};
                r(i) = plot_point(curr.location,point_ticks,point_ticks_color,text,text_offset(1:size(curr.location,1),1),point_args,text_args,group_argin);
            case 'point_pair'
                text_args = {'Color',curr_color,text_argin{:}};
                point_args = {'Marker',marker_style,'MarkerSize',marker_size,'MarkerEdgeColor',curr_color,'MarkerFaceColor',curr_color,line_argin{:}};
                r(i) = plot_point_pair(curr.p1,curr.p2,point_ticks,point_ticks_color,text,text_offset(1:size(curr.p1,1),1),point_args,text_args,group_argin);
            % Line.
            case 'line'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                r(i) = plot_line(limit_mode_auto,bounds,curr.direction,curr.location,text,text_offset(1:size(curr.direction,1),1),line_args,text_args,group_argin);
            % Plane.
            case 'plane'
                text_args = {'Color',curr_color,text_argin{:}};
                patch_args = {'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none','LineStyle','none'};
                r(i) = plot_plane(limit_mode_auto,bounds,curr.direction,curr.location,text,text_offset(1:size(curr.direction,1),1),patch_args,text_args,group_argin);
            % Circle.
            case 'circle'
                text_args = {'Color',curr_color,text_argin{:}};
                line_args = {'LineStyle',line_style,'LineWidth',line_width,'Color',curr_color,line_argin{:},'Marker','none'};
                r(i) = plot_circle(resolution,curr.direction,curr.location,curr.radius,text,text_offset(1:size(curr.location,1),1),line_args,text_args,group_argin);
            % Sphere.
            case 'sphere'
                text_args = {'Color',curr_color,text_argin{:}};
                patch_args = {'FaceColor',curr_color,'FaceAlpha',face_alpha,patch_argin{:},'Marker','none','LineStyle','none'};
                r(i) = plot_sphere(resolution/2,curr.location,curr.radius,text,text_offset(1:size(curr.location,1),1),patch_args,text_args,group_argin);
            % Unknown.
            otherwise
                r(i) = NaN;
                warning('GAToolbox:UndefinedPlot','Plot function is not defined for multivectors of type ''%s''.',curr.type)
        end
    end
end

% Set output arguments.
if nargout == 1
    hp = r;
end

% Plots the given text.
function plot_text(string,position,text_args,group_args)

if ~isempty(string)
    dims = length(position);
    switch dims
        case 1, text('FontName','Times New Roman','FontSize',12,text_args{:},group_args{:},'String',string,'Position',[position;0;0],'Interpreter','latex')
        case 2, text('FontName','Times New Roman','FontSize',12,text_args{:},group_args{:},'String',string,'Position',[position;0],'Interpreter','latex')
        case 3, text('FontName','Times New Roman','FontSize',12,text_args{:},group_args{:},'String',string,'Position',position,'Interpreter','latex')
    end
end

% Plots the given vector.
function [r] = plot_vector(resolution,head_length,weight,direction,location,text,text_offset,line_args,head_args,text_args,group_args)

dims = length(location);
switch dims
    case 1
        x = [weight weight-head_length(1) weight-head_length(1)]*direction;
        y = [0 0.5*head_length(2) -0.5*head_length(2)];
        
        r = hggroup(group_args{:});
        line(line_args{:},'XData',[0 weight*direction(1)]+location(1),'YData',[0 0],'ZData',[],'Parent',r)
        patch(head_args{:},'XData',x+location(1),'YData',y,'ZData',[],'Parent',r)
    case 2
        x = [weight weight-head_length(1) weight-head_length(1)];
        y = [0 0.5*head_length(2) -0.5*head_length(2)];
        
        angle = acos(direction(1));
        if angle ~= 0
            M = makehgtform('axisrotate',[0 0 direction(2)],angle); %TODO Bug! Divisão por zero.
            M = M(1:2,1:2);
        else
            M = eye(2,2);
        end
        p = M*[x;y];
        
        r = hggroup(group_args{:});
        line(line_args{:},'XData',[0 weight*direction(1)]+location(1),'YData',[0 weight*direction(2)]+location(2),'ZData',[],'Parent',r)
        patch(head_args{:},'XData',p(1,:)+location(1),'YData',p(2,:)+location(2),'ZData',[],'Parent',r)
    case 3
        [z y x] = cylinder([1 0],resolution);
        x = (((x - 1) * head_length(1)) + 1) * weight;
        y = y * weight * head_length(2) * 0.5;
        z = z * weight * head_length(2) * 0.5;

        angle = acos(dot([1 0 0],direction/sqrt(sum(direction.^2))));
        if angle ~= 0
            if angle ~= pi
                M = makehgtform('axisrotate',cross([1 0 0],direction),angle);
                M = M(1:3,1:3);
            else
                M = makehgtform('axisrotate',[0 1 0],angle);
                M = M(1:3,1:3);
            end
        else
            M = eye(3,3);
        end
        p1 = M*[x(1,:);y(1,:);z(1,:)];
        p2 = M*[x(2,:);y(2,:);z(2,:)];

        r = hggroup(group_args{:});
        line(line_args{:},'XData',[0 weight*direction(1)]+location(1),'YData',[0 weight*direction(2)]+location(2),'ZData',[0 weight*direction(3)]+location(3),'Parent',r)
        patch(head_args{:},surf2patch([p1(1,:);p2(1,:)]+location(1),[p1(2,:);p2(2,:)]+location(2),[p1(3,:);p2(3,:)]+location(3)),'Parent',r)
        patch(head_args{:},'XData',p1(1,:)+location(1),'YData',p1(2,:)+location(2),'ZData',p1(3,:)+location(3),'Parent',r)
    otherwise
        r = NaN;
        warning('GAToolbox:UndefinedPlot','Plot function is not defined for vectors in %d-D space.',dims)
end

if ~isnan(r)
    plot_text(text,location+weight*direction+text_offset,text_args,{'Parent',r});
end


% Plots the given bivector.
function [r] = plot_bivector(resolution,orientation,head_length,weight,direction,location,text,text_offset,plane_args,arrow_line_args,arrow_tip_args,text_args,group_args)

dims = length(location);
if dims == 3
    [x y] = circle(resolution);
    
    R = [-0.1736 0.9848 0; -0.9848 -0.1736 0; 0 0 1];
    M = [direction,cross(direction(:,1),direction(:,2))]*weight;
    p = M*[x;y;zeros(size(x))];
    l = M*0.5*[x(1:resolution/2);y(1:resolution/2);zeros(1,resolution/2)];
    h = M*R*[0 -head_length(1) -head_length(1); 0 0.5*head_length(2) -0.5*head_length(2); 0 0 0];

    r = hggroup(group_args{:});
    if orientation
        line(arrow_line_args{:},'XData',l(1,:)+location(1),'YData',l(2,:)+location(2),'ZData',l(3,:)+location(3),'Parent',r)
        patch(arrow_tip_args{:},'XData',h(1,:)+l(1,end)+location(1),'YData',h(2,:)+l(2,end)+location(2),'ZData',h(3,:)+l(3,end)+location(3),'Parent',r)
    end
    patch(plane_args{:},'XData',p(1,:)+location(1),'YData',p(2,:)+location(2),'ZData',p(3,:)+location(3),'Parent',r)
    
    plot_text(text,p(:,1)+location+text_offset,text_args,{'Parent',r});
else
    r = NaN;
    warning('GAToolbox:UndefinedPlot','Plot function is not defined for bivectors in %d-D space.',dims)
end


% Plots the given point.
function [r] = plot_point(location,point_ticks,point_ticks_color,text,text_offset,point_args,text_args,group_args)

dims = length(location);

if 1 <= dims && dims <= 3
    r = hggroup(group_args{:});
    
    switch lower(point_ticks)
        case 'orthographic'
            line('XData',[location(1) 0],'YData',[0 0],'ZData',[],'Color',point_ticks_color,'LineStyle',':','Parent',r)

            if dims >= 2
                line('XData',[location(1)           0],'YData',[location(2) location(2)],'ZData',[],'Color',point_ticks_color,'LineStyle',':','Parent',r)
                line('XData',[location(1) location(1)],'YData',[location(2)           0],'ZData',[],'Color',point_ticks_color,'LineStyle',':','Parent',r)
                line('XData',[         0            0],'YData',[location(2)           0],'ZData',[],'Color',point_ticks_color,'LineStyle',':','Parent',r)
            end

            if dims == 3
                line('XData',[location(1)           0],'YData',[location(2) location(2)],'ZData',[location(3) location(3)],'Color',point_ticks_color,'LineStyle',':','Parent',r)
                line('XData',[location(1) location(1)],'YData',[location(2)           0],'ZData',[location(3) location(3)],'Color',point_ticks_color,'LineStyle',':','Parent',r)
                line('XData',[location(1) location(1)],'YData',[location(2) location(2)],'ZData',[location(3)           0],'Color',point_ticks_color,'LineStyle',':','Parent',r)
                line('XData',[          0           0],'YData',[location(2)           0],'ZData',[location(3) location(3)],'Color',point_ticks_color,'LineStyle',':','Parent',r)
                line('XData',[          0           0],'YData',[location(2) location(2)],'ZData',[location(3)           0],'Color',point_ticks_color,'LineStyle',':','Parent',r)
                line('XData',[location(1)           0],'YData',[          0           0],'ZData',[location(3) location(3)],'Color',point_ticks_color,'LineStyle',':','Parent',r)
                line('XData',[location(1) location(1)],'YData',[          0           0],'ZData',[location(3)           0],'Color',point_ticks_color,'LineStyle',':','Parent',r)
                line('XData',[          0           0],'YData',[          0           0],'ZData',[location(3)           0],'Color',point_ticks_color,'LineStyle',':','Parent',r)
            end
            
        case 'origin'
            switch dims
                case 2, line('XData',[location(1) 0],'YData',[location(2) 0],'ZData',[],'Color',point_ticks_color,'LineStyle',':','Parent',r);
                case 3, line('XData',[location(1) 0],'YData',[location(2) 0],'ZData',[location(3) 0],'Color',point_ticks_color,'LineStyle',':','Parent',r);
            end
    end

    switch dims
        case 1, line(point_args{:},'XData',location(1),'YData',0,'ZData',[],'Parent',r);
        case 2, line(point_args{:},'XData',location(1),'YData',location(2),'ZData',[],'Parent',r);
        case 3, line(point_args{:},'XData',location(1),'YData',location(2),'ZData',location(3),'Parent',r);
    end
    
    plot_text(text,location+text_offset,text_args,{'Parent',r});
else
    r = NaN;
    warning('GAToolbox:UndefinedPlot','Plot function is not defined for points in %d-D space.',dims)
end


% Plots the given point pair.
function [r] = plot_point_pair(location1,location2,point_ticks,point_ticks_color,text,text_offset,point_args,text_args,group_args)

r = hggroup(group_args{:});
plot_point(location1,point_ticks,point_ticks_color,text,text_offset,{point_args{:}},text_args,{'Parent',r});
plot_point(location2,point_ticks,point_ticks_color,'',zeros(size(location2)),{point_args{:}},text_args,{'Parent',r});


% Plots the given line.
function [r] = plot_line(limit_mode_auto,bounds,direction,location,text,text_offset,line_args,text_args,group_args)

dims = length(location);
switch dims
    case 2
        if limit_mode_auto(1)
            warning('GAToolbox:AxisLimits','Set the axis limits before plot lines (refer to the MATLAB <a href="matlab:doc axis">axis</a> reference page for more information).')
        end

        r = hggroup(group_args{:});

        points = sortrows(intersect_lines(location',direction',[bounds(1,1) bounds(2,1); bounds(1,2) bounds(2,1); bounds(1,1) bounds(2,1); bounds(1,1) bounds(2,2)],[0 1; 0 1; 1 0; 1 0]));
        if isfinite(points(3,1))
            line(line_args{:},'XData',points(2:3,1),'YData',points(2:3,2),'ZData',[],'Parent',r);
        else
            line(line_args{:},'XData',points(1:2,1),'YData',points(1:2,2),'ZData',[],'Parent',r);
        end
    case 3
        if limit_mode_auto(1) || limit_mode_auto(2)
            warning('GAToolbox:AxisLimits','Set the axis limits before plot lines (refer to the MATLAB <a href="matlab:doc axis">axis</a> reference page for more information).')
        end
        
        r = hggroup(group_args{:});

        points = sortrows(intersect_line_planes(location',direction',[bounds(1,1) bounds(2,1) bounds(3,1); bounds(1,2) bounds(2,1) bounds(3,1); bounds(1,1) bounds(2,1) bounds(3,1); bounds(1,1) bounds(2,2) bounds(3,1); bounds(1,1) bounds(2,1) bounds(3,1); bounds(1,1) bounds(2,1) bounds(3,2)],[0 1 0; 0 1 0; 1 0 0; 1 0 0; 1 0 0; 1 0 0],[0 0 1; 0 0 1; 0 0 1; 0 0 1; 0 1 0; 0 1 0]));
        nv = sum(~isnan(line_position_3d(points,location',direction')))/2;
        points = points((nv:nv+1),:);
        
        line(line_args{:},'XData',points(:,1),'YData',points(:,2),'ZData',points(:,3),'Parent',r);
    otherwise
        r = NaN;
        warning('GAToolbox:UndefinedPlot','Plot function is not defined for lines in %d-D space.',dims)
end

if ~isnan(r)
    plot_text(text,points(2,:)'+text_offset,text_args,{'Parent',r});
end


% Plots the given line and its projetion onto the parabola of the Conformal model.
function plot_line_parabola(resolution,limit_mode_auto,bounds,direction,location,line_args,group_args)

if limit_mode_auto(1)
    warning('GAToolbox:AxisLimits','Set the axis limits before plot lines (refer to the MATLAB <a href="matlab:doc axis">axis</a> reference page for more information).')
end

points = sortrows(intersect_lines(location',direction',[bounds(1,1) bounds(2,1); bounds(1,2) bounds(2,1); bounds(1,1) bounds(2,1); bounds(1,1) bounds(2,2)],[0 1; 0 1; 1 0; 1 0]));

if isfinite(points(3,1))
    x = points(2:3,1);
    y = points(2:3,2);
else
    x = points(1:2,1);
    y = points(1:2,2);
end
line(line_args{:},group_args{:},'XData',x,'YData',y,'ZData',[])

%TODO Bug!
x = x(1):((x(2)-x(1))/resolution):x(2);
y = y(1):((y(2)-y(1))/resolution):y(2);
z = x.^2+y.^2;

%TODO Este corte é grosseiro.
visible = z<=bounds(3,2);
x = x(visible);
y = y(visible);
z = z(visible);

line(line_args{:},group_args{:},'XData',x,'YData',y,'ZData',z)


% Plots the given plane.
function [r] = plot_plane(limit_mode_auto,bounds,direction,location,text,text_offset,patch_args,text_args,group_args)

dims = length(location);
if dims == 3
    if limit_mode_auto(1) || limit_mode_auto(2)
        warning('GAToolbox:AxisLimits','Set the axis limits before plot lines (refer to the MATLAB <a href="matlab:doc axis">axis</a> reference page for more information).')
    end

    points = intersect_plane_lines(location',direction(:,1)',direction(:,2)',[bounds(1,1) bounds(2,1) bounds(3,1); bounds(1,1) bounds(2,1) bounds(3,2); bounds(1,1) bounds(2,2) bounds(3,1); bounds(1,1) bounds(2,2) bounds(3,2); bounds(1,1) bounds(2,1) bounds(3,1); bounds(1,1) bounds(2,1) bounds(3,2); bounds(1,2) bounds(2,1) bounds(3,1); bounds(1,2) bounds(2,1) bounds(3,2); bounds(1,1) bounds(2,1) bounds(3,1); bounds(1,1) bounds(2,2) bounds(3,1); bounds(1,2) bounds(2,1) bounds(3,1); bounds(1,2) bounds(2,2) bounds(3,1)],[1 0 0; 1 0 0; 1 0 0; 1 0 0; 0 1 0; 0 1 0; 0 1 0; 0 1 0; 0 0 1; 0 0 1; 0 0 1; 0 0 1]);

    bounds(:,1) = bounds(:,1) - 1e-10;
    bounds(:,2) = bounds(:,2) + 1e-10;
    points = points(((points(:,1) >= bounds(1,1)) & (points(:,1) <= bounds(1,2)) & (points(:,2) >= bounds(2,1)) & (points(:,2) <= bounds(2,2)) & (points(:,3) >= bounds(3,1)) & (points(:,3) <= bounds(3,2))),:);

    x = line_position_3d(points,location',direction(:,1)');
    y = line_position_3d(points,location',direction(:,2)');
    if ~isempty(x) && ~isempty(y)
        index = convhull(x,y);
        index = index(1:end-1);

        r = hggroup(group_args{:});
        patch(patch_args{:},'XData',points(index,1),'YData',points(index,2),'ZData',points(index,3),'Parent',r);
    else
        r = NaN;
    end
else
    r = NaN;
    warning('GAToolbox:UndefinedPlot','Plot function is not defined for planes in %d-D space.',dims)
end

if ~isnan(r) && size(points,1)>0
    plot_text(text,points(1,:)'+text_offset,text_args,{'Parent',r});
end


% Plots the given circle.
function [r] = plot_circle(resolution,direction,location,radius,text,text_offset,line_args,text_args,group_args)

dims = length(location);
switch dims
    case 2
        [x y] = circle(resolution);
        r = hggroup(group_args{:});
        line(line_args{:},'XData',x*radius+location(1),'YData',y*radius+location(2),'ZData',[],'Parent',r);
    case 3
        [x y] = circle(resolution);
        p = [direction,cross(direction(:,1),direction(:,2))]*radius*[x;y;zeros(size(x))];
        r = hggroup(group_args{:});
        line(line_args{:},'XData',p(1,:)+location(1),'YData',p(2,:)+location(2),'ZData',p(3,:)+location(3),'Parent',r);
    otherwise
        r = NaN;
        warning('GAToolbox:UndefinedPlot','Plot function is not defined for circles in %d-D space.',dims)
end

if ~isnan(r)
    plot_text(text,location+text_offset,text_args,{'Parent',r});
end


% Plots the given circle and its projetion onto the parabola of the Conformal model.
function plot_circle_parabola(resolution,bounds,location,radius,line_args,group_args)

[x y] = circle(resolution);
x = x*radius+location(1);
y = y*radius+location(2);
z = x.^2+y.^2;

warning('Remover isso depois. Foi colocado para o paper.')
z = sign(radius)*z;

%TODO Este corte é grosseiro.
visible = z<=bounds(3,2);
x = x(visible);
y = y(visible);
z = z(visible);

line(line_args{:},group_args{:},'XData',x,'YData',y,'ZData',[]);
line(line_args{:},group_args{:},'XData',x,'YData',y,'ZData',z)


% Plots the given sphere.
function [r] = plot_sphere(resolution,location,radius,text,text_offset,patch_args,text_args,group_args)

dims = length(location);
if dims == 3
    [x y z] = sphere(resolution);
    r = hggroup(group_args{:});
    patch(patch_args{:},surf2patch(x*radius+location(1),y*radius+location(2),z*radius+location(3)),'Parent',r);
    plot_text(text,location+text_offset,text_args,{'Parent',r});
else
    r = NaN;
    warning('GAToolbox:UndefinedPlot','Plot function is not defined for spheres in %d-D space.',dims)
end


% Generates n+1 points over an unit circle.
function [x y] = circle(n)

t = 0:(2*pi/n):(2*pi);

x = cos(t);
x(end+1) = x(1);

y = sin(t);
y(end+1) = y(1);


% Returns the intersection point of a line and other lines in 2D.
function [r] = intersect_lines(p1,d1,p2,d2)

parallel = (d1(1)*d2(:,2) == d2(:,1)*d1(2));
colinear = ((p2(:,1)-p1(1))*d1(2) == (p2(:,2)-p1(2))*d1(1)) & parallel ;
other = ~parallel;

r = zeros(size(p2,1),2);
r(colinear,:) = Inf;
r(parallel&~colinear,:) = NaN;
r(other,1) = ((p2(other,2)-p1(2))*d1(1).*d2(other,1) + p1(1)*d1(2)*d2(other,1) - p2(other,1).*d2(other,2)*d1(1)) ./ (d2(other,1)*d1(2)-d1(1)*d2(other,2));
r(other,2) = ((p2(other,1)-p1(1))*d1(2).*d2(other,2) + p1(2)*d1(1)*d2(other,2) - p2(other,2).*d2(other,1)*d1(2)) ./ (d1(1)*d2(other,2)-d2(other,1)*d1(2));


% Returns the intersection points of a line and some planes in 3D.
function [r] = intersect_line_planes(p1,d1,p2,v1,v2)

p1 = repmat(p1,size(p2,1),1);
d1 = repmat(d1,size(p2,1),1);

n = cross(v1,v2,2);

parallel = (dot(n,d1,2) == 0);
other = ~parallel;

t = dot(n(other,:),p2(other,:)-p1(other,:),2) ./ dot(n(other,:),d1(other,:),2);

r = zeros(size(p2,1),3);
r(parallel,:) = NaN;
r(other,:) = p1(other,:) + repmat(t,1,3).*d1(other,:);


% Returns the intersection points of a plane and some lines in 3D.
function [r] = intersect_plane_lines(p1,v1,v2,p2,d2)

p1 = repmat(p1,size(p2,1),1);

n = cross(v1,v2);
n = repmat(n,size(p2,1),1);

parallel = (dot(n,d2,2) == 0);
other = ~parallel;

t = dot(n(other,:),p1(other,:)-p2(other,:),2) ./ dot(n(other,:),d2(other,:),2);

r = zeros(size(p1,1),3);
r(parallel,:) = NaN;
r(other,:) = p2(other,:) + repmat(t,1,3).*d2(other,:);


% Returns the position of 3D points on a 3D line.
function [r] = line_position_3d(p1,p2,d2)

p2 = repmat(p2,size(p1,1),1);
d2 = repmat(d2,size(p1,1),1);

r = dot(p1-p2,d2,2) ./ dot(d2,d2,2);