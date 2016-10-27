# ih-calendar
A bare minimum calendar for the CLI.

## Disclaimer
A lot of these "How to"s may be incorrect, there may be some detail I've missed.
This is a WIP after all.

## How to install

### *nix
Simply download the program and run `make`. This will create an executable file
`ih-calendar`. You can put this wherever, there isn't a `make install` yet.

### Windows
Godspeed.

## How to use
`ih-calendar` is very easy to use. The program takes a command as the first
argument, the remaining arguments are for the command itself.

Here's a list:

`print [YEAR] [MONTH]` - prints dates and their day of the week for
YEAR/MONTH.

`add [YEAR] [MONTH] [DAY] [HOUR] [MINUTE] [INFO]` - adds a new entry in the
calendar. The `[INFO]` argument must be a single argument string (So if you
want whitespace, you have to surround the text with quotation marks).

`list` - lists all entries in the calendar in order they were added.

## How to configure
This is required at the moment, due to the lack of a `make install`.

### Defining the config file location
The program tries to find a config file upon starting, first it will check if
the enviroment variable `ih_calendar_conf_lctn` has been set, if so it will use
that file as the config file. Otherwise it uses `~/.config/ih_calendar`. If that
file also does not exist, the program terminates.

### The syntax
The syntax of the config file is very simple:

`variable=value`

No quotation marks, no semi colons, no nothing. It currently does not support
comments.

### Config variables
At the moment only one variable exists. It is obligatory.

`data_file_lctn` - Path to location of data file. Note: The path _must_ be
absolute (ie. no '~'), it is not yet supported.

## License
>ih-calendar - A bare minimum calendar for the CLI.
>Copyright (C) 2016  Sebastian Vikkelsø Elleholm
>
>This program is free software: you can redistribute it and/or modify
>it under the terms of the GNU General Public License as published by
>the Free Software Foundation, either version 3 of the License, or
>(at your option) any later version.
>
>This program is distributed in the hope that it will be useful,
>but WITHOUT ANY WARRANTY; without even the implied warranty of
>MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>GNU General Public License for more details.
>
>You should have received a copy of the GNU General Public License
>along with this program.  If not, see <http://www.gnu.org/licenses/>.

Full license can be found in the `LICENSE` file.
