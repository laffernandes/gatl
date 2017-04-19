function [vargout] = axis_2h(varargin)

% Set some default properties.
face_alpha = 0.25;
face_color = [0.5 0.5 0.5];

% Set bounds.
bounds = [-1 1 -1 1 -0.0001 2];
if nargin ~= 0
    arg1 = double(varargin{1});
    bounds(1:numel(arg1)) = arg1(:);
end

% Create axis.
if nargout == 0
	axis([bounds varargin{2:end}])
else
	vargout{:} = axis([bounds varargin{2:end}]);
end
set(gca,'UserData','ga2h_axis')

% Label the axis.
% xlabel(ga2latex('\vectorei{1}'),'Interpreter','latex','FontName','Times New Roman','FontSize',12)
% ylabel(ga2latex('\vectorei{2}'),'Interpreter','latex','FontName','Times New Roman','FontSize',12)
% zlabel(ga2latex('\vectorei{0}'),'Interpreter','latex','FontName','Times New Roman','FontSize',12)

% Set axis aspect ratio.
axis equal

% Display box.
box on

% Plot plane e0 = 1.
X = [bounds(1) bounds(1) bounds(2) bounds(2)];
Y = [bounds(3) bounds(4) bounds(4) bounds(3)];
Z = [1 1 1 1];
patch('XData',X,'YData',Y,'ZData',Z,'FaceColor',face_color,'FaceAlpha',face_alpha,'Marker','none','LineStyle','none')