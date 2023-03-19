#include <bits/stdc++.h>

using namespace std ;

vector < pair < int , int > > points ;

vector<vector<double>> cost_matrix ;

int n = 100 ;

double dist_minimum = 10 ;

map < pair < int , int > , bool > visit ;

double calc_dist ( int pos , int pos_1 ){
    double dist_x = points [ pos ].first - points[ pos_1 ].first ;
    double dist_y = points [ pos ].second - points[ pos_1 ].second ;
    double dist = sqrt ( dist_x * dist_x + dist_y * dist_y ) ;
    return dist ;
}

int main ( ){
    srand(time(NULL));
    for ( int i = 0 ; i < n ; i++ ){
        int x , y ;
        while ( true ) {
            x = rand ( ) % 2000 ;
            y = rand ( ) % 2000 ;
            bool check = true ;
            if ( visit [ { x , y } ] ) continue ;
            points.push_back ( { x , y } ) ;
            for ( int d = 0 ; d < i ; d++ ){
                if ( calc_dist ( d , i ) < dist_minimum ) check = false ;
            }
            points.pop_back ( ) ;
            if ( check ) break ;

        }
        visit [ { x , y } ] = true ;
        vector < double > cost ;
        points.push_back ( { x , y } ) ;
        for ( int d = 0 ; d < i ; d++ ){
            cost_matrix [ d ].push_back ( calc_dist ( d , i )  ) ;
            cost.push_back ( calc_dist ( d , i )  ) ;
        }
        cost.push_back ( 0 ) ;
        cost_matrix.push_back ( cost ) ;
    }
    /*for ( int i = 0 ; i < n ; i++ ){
        for ( int d = 0 ; d < n ; d++ ){
            cout << cost_matrix [ i ][ d ] << " " ;
        }
        cout<<endl;
    }*/

    return 0 ;
}
