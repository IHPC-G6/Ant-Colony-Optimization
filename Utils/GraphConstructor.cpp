#include <bits/stdc++.h>

using namespace std ;

vector < pair < int , int > > points ;

double min_distance = 100.0 ;

map < pair < int , int > , bool > visit ;

double distance ( int pos , int pos_1 ){
    double dist_x = points [ pos ].first - points[ pos_1 ].first ;
    double dist_y = points [ pos ].second - points[ pos_1 ].second ;
    double dist = sqrt ( dist_x * dist_x + dist_y * dist_y ) ;
    return dist ;
}

pair<vector<vector<double>>, vector<pair<int, int>>> BuildGraph ( int n ){

    vector<vector<double>> cost_matrix ;

    srand(time(NULL));
    for ( int i = 0 ; i < n ; i++ ){
        int x , y ;
        while ( true ) {
            x = rand ( ) % 2001 ;
            y = rand ( ) % 2001 ;
            bool check = true ;
            if ( visit [ { x , y } ] ) continue ;
            points.push_back ( { x , y } ) ;
            for ( int d = 0 ; d < i ; d++ ){
                if ( distance ( d , i ) < min_distance ) check = false ;
            }
            points.pop_back ( ) ;
            if ( check ) break ;

        }
        visit [ { x , y } ] = true ;
        vector < double > cost ;
        points.push_back ( { x , y } ) ;
        for ( int d = 0 ; d < i ; d++ ){
            cost_matrix [ d ].push_back ( distance ( d , i )  ) ;
            cost.push_back ( distance ( d , i )  ) ;
        }
        cost.push_back ( 0 ) ;
        cost_matrix.push_back ( cost ) ;
    }

    return { cost_matrix, points } ;
}
