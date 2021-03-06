#ifndef LANE_POINTS_CALCULATOR_HPP_
#define LANE_POINTS_CALCULATOR_HPP_

#include <opencv2/opencv.hpp>
#include "lane_detection/image_processor.hpp"

using namespace cv;

enum Direction
{
    LEFT,
    RIGHT
};
enum SearchMode
{
    FIXED_DIST,
    MIDDLE,
    MIDDLE_FALLBACK
};

/**
 * This class offers methods to determine lane points and trajectory points derived from these
 * in an image which is contained in an ImageProcessor.
 *
 */
class LanePointsCalculator
{
  public:
    static LanePointsCalculator& getInstance() {
        static LanePointsCalculator instance;
        return instance;
    }

    /**
     * Calculates a point orthogonal to the line between start and end point,
     * with a given distance from the middle of these two points.
     * The given direction specifies if the point is calculated 90 degrees on the left or right side.
     * @param start
     * @param end
     * @param dir
     * @param dist
     * @return
     */
    Point2i orthoPoint(Point2i start, Point2i end, Direction dir, double dist);

    /**
     * Searches for the right or left lane in a given image row.
     * If found, the innermost pixel of this lane is returned.
     * @param searchDir
     * @param row
     * @param proc
     * @return
     */
    Point2i innerLanePoint(Direction searchDir, int row, ImageProcessor &proc);

    /**
     * Searches in the given rows for lane pixels and calculates trajectory points from these.
     * @param rows
     * @param rows_size
     * @param searchDir specifies from which side the search is done (LEFT for finding the right, RIGHT for finding the left lane first)
     * @param searchMode specifies how trajectory points should be calculated, can be one of the following:
     *     FIXED_DIST calculates all points with a fixed distance from the first found lane
     *     MIDDLE only finds points for rows where both lanes can be detected
     *     MIDDLE_FALLBACK prefers calculating middle points and uses the distance as a fallback
     * @param distance
     * @param proc
     * @return
     */
    std::vector<Point2i> trajPointsSimple(int *rows, int rows_size, Direction searchDir, SearchMode searchMode, int distance, ImageProcessor &proc);

    /**
     * Calculates the innermost lane points in the given rows of the image.
     * @param rows
     * @param rows_size
     * @param searchDir
     * @param proc
     * @return
     */
    std::vector<Point2i> lanePoints(int *rows, int rows_size, Direction searchDir, ImageProcessor &proc);

    /**
       * Calculates a single (inaccurate) trajectory point by using a fixed distance to the right lane in the given distance (y_cm).
       */
    Point2d singleTrajPoint(double rightLaneDist_cm, double y_cm, int colorThreshold, Mat& image, CameraCalibration& cal);

private:
    LanePointsCalculator(){};
    LanePointsCalculator(LanePointsCalculator const&) = delete;
    void operator=(LanePointsCalculator const&) = delete;
};

#endif // LANE_POINTS_CALCULATOR_HPP_
