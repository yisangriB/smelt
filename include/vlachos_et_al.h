#ifndef _VLACHOS_ET_AL_H_
#define _VLACHOS_ET_AL_H_

#include <memory>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include "distribution.h"
#include "stochastic_model.h"

namespace stochastic {
/**
 * Stochastic model for generating scenario specific ground
 * motion time histories. This is based on the paper:
 * Vlachos C., Papakonstantinou K.G., & Deodatis G. (2018).
 * Predictive model for site specific simulation of ground motions based on
 * earthquake scenarios. Earthquake Engineering & Structural Dynamics, 47(1),
 * 195-218.
 */
class VlachosEtAl : public StochasticModel {
 public:
  /**
   * @constructor Delete default constructor
   */
  VlachosEtAl() = delete;

  /**
   * @constructor Construct scenario specific ground motion model based on input
   * parameters
   * @param[in] moment_magnitude Moment magnitude of earthquake scenario
   * @param[in] rupture_distance Closest-to-site rupture distance in kilometers
   * @param[in] vs30 Soil shear wave velocity averaged over top 30 meters in
   *                 meters per second
   * @param[in] time_step Temporal discretization. Defaults to 0.01 seconds.
   * @param[in] freq_step Frequency discretization. Defaults to 0.2 Hz.
   * @param[in] num_spectra Number of evolutionary power spectra that should be
   *                        generated. Default value is 1.
   * @param[in] num_sims Number of simulated ground motion time histories that
   *                     should be generated per evolutionary power
   */
  VlachosEtAl(double moment_magnitude, double rupture_distance, double vs30,
              double time_step = 0.01, double freq_step = 0.2,
              unsigned int num_spectra = 1;
              unsigned int num_sims = 1);

  /**
   * @destructor Virtual destructor
   */
  virtual ~VlachosEtAl() {};

  /**
   * Get the name of the stochastic model
   * @return Model name as a string
   */
  std::string model_name() const override { return model_name_ };

  /**
   * Generate ground motion time histories based on input parameters
   */
  void generate() override;

  /**
   * Get the generated ground motion time histories in JSON wrapper
   * class format
   * @return Desires time histories in JSON wrapper class format
   */
  utilities::JsonWrapper wrapped_json_results() const override;

  /**
   * Get the generated ground motion time histories in string format
   * @return Desired time histories in string format
   */
  std::string json_results() const override;

 private:
  std::string model_name_; /**< Name of stochastic model */
  double moment_magnitude_; /**< Moment magnitude for scenario */
  double rupture_dist_; /**< Closest-to-site rupture distance in kilometers */
  double vs30_; /**< Soil shear wave velocity averaged over top 30 meters in
                   meters per second */
  double time_step_; /**< Temporal discretization */
  double freq_step_; /**< Frequency discretization */
  unsigned int num_spectra_; /**< Number of evolutionary power spectra that
                                should be generated */
  unsigned int num_sims_; /**< Number of simulated ground motion time histories
                             that should be generated per evolutionary power
                             spectrum */
  std::vector<std::shared_ptr<stochastic::Distribution>>
      model_parameters_; /**< Distrubutions for 18-parameter model */
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
      parameter_realizations_; /**< Random realizations of model parameters */
};
}  // namespace stochastic

#endif  // _VLACHOS_ET_AL_H_
