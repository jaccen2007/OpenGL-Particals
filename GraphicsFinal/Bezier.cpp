#include "Bezier.hpp"
        BezierCalc::BezierCalc(const Point& control0,const Point& control1,const Point& control2,const Point& control3){
            ps.push_back(control0*20);
            ps.push_back(control1*2);
            ps.push_back(control2);
            ps.push_back(control3);
            for(int i=0;i<3;i++){
                ps[1][i]*=3;
                ps[2][i]*=3;
            }
        }
        Point BezierCalc::getColor(double t)const {
            if(t>1||t<0){
                assert(!"bad t Value");
            }

            double oneMinust=1-t;
            Point toReturn;
            for(int i=0;i<3;i++){
                toReturn[i]=oneMinust*oneMinust*oneMinust*ps[0][i]+
                    oneMinust*oneMinust*t*ps[1][i]+
                    oneMinust*t*t*ps[2][i]+
                    t*t*t*ps[3][i];
            }
            return toReturn;

        }

